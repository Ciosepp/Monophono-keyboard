#include <iostream>

using namespace std;
int const nKeys= 49;
int const nArpNotes= 28;
int octaves=0;
int n=0;
char ready ='n';
int NOTES[nArpNotes];
int main()
{
    int c;
    cout<<"Insert #notes:"<<endl;
    cin>>n;
    for(int i=0; i<n; i++){
        cout<<"Insert note"<<endl;
        cin>>NOTES[i];
    }
    cout<<endl;

    for(int i=0; i<n; i++){
        cout<<NOTES[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"Insert #octaves:"<<endl;
    cin>>octaves;

    for(int o=1; o<octaves+1; o++){
        for(int i=0; i<n; i++){
            if((NOTES[i]+o*12)>nKeys)
                break;
            NOTES[i+(o*n)] = (NOTES[i]+o*12)%nKeys;

        }
        cout<<endl;
    }
    for(int i=0; i<n*(octaves+1); i++){
        cout<<NOTES[i]<<" ";
    }

    return 0;
}
