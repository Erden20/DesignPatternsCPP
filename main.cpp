#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


class IObserver {
public:
    virtual void update(double usdRate, double eurRate) = 0;
    virtual ~IObserver() {}
};


class ISubject {
public:
    virtual void addObserver(IObserver* obs) = 0;
    virtual void removeObserver(IObserver* obs) = 0;
    virtual void notifyObservers() = 0;
    virtual ~ISubject() {}
};


class CurrencyExchange : public ISubject {
private:
    vector<IObserver*> observers;
    double usdRate = 0.0;
    double eurRate = 0.0;

public:
    void setRates(double usd, double eur) {
        usdRate = usd;
        eurRate = eur;
        cout << "\n[CurrencyExchange] Курсы обновлены: USD = " << usdRate << ", EUR = " << eurRate << endl;
        notifyObservers();
    }

    void addObserver(IObserver* obs) override {
        
        if (find(observers.begin(), observers.end(), obs) == observers.end())
            observers.push_back(obs);
    }

    void removeObserver(IObserver* obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for (auto obs : observers) {
            if (obs) obs->update(usdRate, eurRate);
        }
    }
};


class MobileAppObserver : public IObserver {
public:
    void update(double usdRate, double eurRate) override {
        cout << "📱 MobileApp: уведомление — USD=" << usdRate << ", EUR=" << eurRate << endl;
    }
};

class WebAppObserver : public IObserver {
public:
    void update(double usdRate, double eurRate) override {
        cout << "🌐 WebApp: обновлён прайс — USD=" << usdRate << ", EUR=" << eurRate << endl;
    }
};

class EmailNotifierObserver : public IObserver {
private:
    string email;
public:
    EmailNotifierObserver(const string& e) : email(e) {}
    void update(double usdRate, double eurRate) override {
        cout << "📧 Email to " << email << ": курсы USD=" << usdRate << ", EUR=" << eurRate << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    CurrencyExchange exchange;

    MobileAppObserver mobile;
    WebAppObserver web;
    EmailNotifierObserver email("student@example.com");


    exchange.addObserver(&mobile);
    exchange.addObserver(&web);
    exchange.addObserver(&email);

    cout << "=== Demo Observer (CurrencyExchange) ===\n";
    cout << "Сценарий: обновляем курсы и смотрим, как подписчики получают уведомления.\n";


    exchange.setRates(478.5, 506.3);


    exchange.setRates(480.2, 508.1);


    cout << "\nУдаляем WebAppObserver (больше не будет получать уведомления)...\n";
    exchange.removeObserver(&web);

    exchange.setRates(481.0, 507.9);

    cout << "\nДемонстрация завершена. Нажмите Enter для выхода...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка
    cin.get();
    return 0;
}
