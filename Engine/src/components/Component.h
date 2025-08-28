#pragma once

class GameObject;

class Component{
    friend class GameObject;
    public:
        virtual ~Component() = default;
        GameObject* getOwner() const { return owner;}

        virtual void init() {}
        virtual void update(float deltaTime) {}
        virtual void render() {}
        void generateID();

    protected:
        GameObject* owner = nullptr;
        int UID = -1;
        static int ID_Count;
};
