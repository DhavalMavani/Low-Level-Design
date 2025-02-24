#include <unordered_set>
#include <iostream>

using namespace std;

class IObserverDisplay{
    public:
        virtual void update()=0;
};

class IDisplay{
    public:
        virtual void display()=0;
};

class IWeatherStation{
    public:
        virtual void registerObserver(IObserverDisplay* observer)=0;
        virtual void unregisterObserver(IObserverDisplay* observer)=0;
        virtual void notify()=0;
};

class WeatherStation: public IWeatherStation{
    public:
        unordered_set<IObserverDisplay*> observersList;
        int temperature, humidity, pressure;

        void registerObserver(IObserverDisplay* observer) override{ observersList.emplace(observer); }

        void unregisterObserver(IObserverDisplay* observer) override{ observersList.erase(observer); }

        void notify() override{
            for(auto &observer: observersList){
                observer->update();
            }
        }

        void setData(int temperature, int humidity, int pressure){
            this->temperature=temperature;
            this->humidity=humidity;
            this->pressure=pressure;
            notify();
        }
};

class phoneDisplay: public IObserverDisplay, public IDisplay{
    public:
        WeatherStation* station=NULL;
        phoneDisplay(WeatherStation* station ) { this->station=station; }

        void update() override { display(); }

        void display() override{ cout<<"Phone display is updated: "<< station->temperature<<" "<<station->humidity<<" "<<station->pressure<<" \n"; }
};

class LaptopDisplay: public IObserverDisplay, public IDisplay{
    public:
        WeatherStation* station=NULL;
        LaptopDisplay(WeatherStation* station ) { this->station=station; }

        void update() override { display(); }

        void display() override{ cout<<"Laptop display is updated: "<< station->temperature<<" "<<station->humidity<<" "<<station->pressure<<" \n"; }
};

int main(){
    WeatherStation* station= new WeatherStation();
    phoneDisplay* phone= new phoneDisplay(station);
    LaptopDisplay* laptop= new LaptopDisplay(station);

    station->registerObserver(phone);
    station->registerObserver(laptop);
    station->setData(3,4,5);

    station->unregisterObserver(laptop);
    station->setData(88,2,333);

    return 0;
}