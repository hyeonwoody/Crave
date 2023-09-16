#include <string>
#include <vector>
#include <memory>

class CMain
{
    
    
    
public:
    CMain(){
    }


    void Init();
    int Main(char* url);
public:
private:
    
};


class CNamuStep
{
public:
    
    virtual bool SetUrl(std::string name);

    typedef struct NamuPage
    {
        std::string name;
        std::vector<std::string> link;
    };


    virtual bool Start();
    virtual bool Stop();
    virtual void ThreadMain();

private:

protected:
    NamuPage* currentTarget;
    bool m_threadActive;
};

class CNamuFrontStep : public CNamuStep
{
public:
    CNamuFrontStep(std::string name){
        currentTarget = new NamuPage;
        currentTarget->name = name;
    }

    ~CNamuFrontStep (){
        delete currentTarget;
    }
    virtual void ThreadMain(); // Declaration in CNamuFrontStep
    //virtual bool Delete ();


protected:

};

class CNamuBackStep : public CNamuStep
{
public:
    CNamuBackStep(std::string name){
        currentTarget = new NamuPage;
        currentTarget->name = name;
    }

    ~CNamuBackStep (){
        delete currentTarget;
    }
    //virtual bool Delete ();

protected:
};
