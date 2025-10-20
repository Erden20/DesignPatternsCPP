#include <iostream>
#include <memory>
#include <string>
using namespace std;


class IPaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~IPaymentStrategy() {}
};


class CreditCardPayment : public IPaymentStrategy {
private:
    string cardNumber;
public:
    CreditCardPayment(const string& number) : cardNumber(number) {}
    void pay(double amount) override {
        cout << "💳 Оплата " << amount << " KZT с банковской карты (" << cardNumber << ")" << endl;
    }
};


class PayPalPayment : public IPaymentStrategy {
private:
    string email;
public:
    PayPalPayment(const string& mail) : email(mail) {}
    void pay(double amount) override {
        cout << "💸 Оплата " << amount << " KZT через PayPal (аккаунт: " << email << ")" << endl;
    }
};


class CryptoPayment : public IPaymentStrategy {
private:
    string walletAddress;
public:
    CryptoPayment(const string& wallet) : walletAddress(wallet) {}
    void pay(double amount) override {
        cout << "🪙 Оплата " << amount << " KZT криптовалютой (кошелёк: " << walletAddress << ")" << endl;
    }
};


class PaymentContext {
private:
    unique_ptr<IPaymentStrategy> strategy;
public:
    void setStrategy(unique_ptr<IPaymentStrategy> newStrategy) {
        strategy = move(newStrategy);
    }

    void executePayment(double amount) {
        if (strategy)
            strategy->pay(amount);
        else
            cout << "⚠️ Стратегия оплаты не выбрана!" << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    PaymentContext context;

    cout << "=== Demo Паттерна 'Стратегия' ===" << endl;
    cout << "Выберите способ оплаты:" << endl;
    cout << "1 - Банковская карта" << endl;
    cout << "2 - PayPal" << endl;
    cout << "3 - Криптовалюта" << endl;

    int choice;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
        case 1:
            context.setStrategy(make_unique<CreditCardPayment>("1234-5678-9012-3456"));
            break;
        case 2:
            context.setStrategy(make_unique<PayPalPayment>("user@example.com"));
            break;
        case 3:
            context.setStrategy(make_unique<CryptoPayment>("0xABCDEF1234567890"));
            break;
        default:
            cout << "❌ Неверный выбор!" << endl;
            return 0;
    }

    double amount;
    cout << "\nВведите сумму оплаты (в KZT): ";
    cin >> amount;

    cout << endl;
    context.executePayment(amount);

    cout << "\n✅ Оплата завершена. Нажмите Enter для выхода...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
