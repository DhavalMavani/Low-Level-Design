#include <iostream>
using namespace std;

class IButton{
public:
    virtual void press()=0;
};

class ITextBox{
public:
    virtual void setText()=0;
};

class IGUIFactory{
public:
    virtual IButton* createButton()=0;
    virtual ITextBox* createTextBox()=0;

    static IGUIFactory* createFactory(string os);
};



class MacButton: public IButton{
public:
    void press() override{ cout<<"Pressed mac button\n"; }
};

class MacTextBox: public ITextBox{
public:
    void setText() override{ cout<<"Set mac text\n"; }
};

class MacFactory: public IGUIFactory{
    public:
    IButton* createButton() override{ return new MacButton(); }
    ITextBox* createTextBox() override{ return new MacTextBox(); }
};



class WindowsButton: public IButton{
    public:
    void press() override{ cout<<"Pressed windows button\n"; }
};

class WindowsTextBox: public ITextBox{
    public:
    void setText() override{ cout<<"Set windows text\n"; }
};

class WindowsFactory: public IGUIFactory{
    public:
    IButton* createButton() override{ return new WindowsButton(); }
    ITextBox* createTextBox() override{ return new WindowsTextBox(); }
};

IGUIFactory* IGUIFactory::createFactory(string os){
    if(os=="mac") return new MacFactory();
    else if(os=="windows") return new WindowsFactory();
    else return NULL;
}


int main(){
    string os;
    cin>>os;

    IGUIFactory* factory= IGUIFactory::createFactory(os);

    IButton* button = factory->createButton();
    ITextBox* textbox = factory->createTextBox();

    button->press();
    textbox->setText();

    delete factory;
    delete button;
    delete textbox;
}
