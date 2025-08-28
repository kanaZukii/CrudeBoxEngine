#include "Component.h"

int Component::ID_Count;

void Component::generateID(){
    if(UID < 0){
        UID = ID_Count;
        ID_Count++;
    }
}
