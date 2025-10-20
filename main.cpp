#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Интерфейс стратегии
class IPaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~IPaymentStrategy() {}
};

// Реализация оплаты банковской картой
class CreditCardPayment : public IPaymentStrategy {
    string cardNumber;
public:
    CreditCardPayment(string number) : cardNumber(number) {}
    void pay(double amount) override {
        cout << "Оплата " << amount << " тенге через банковскую карту: " << cardNumber << endl;
    }
};

// Реализация оплаты через PayPal
class PayPalPayment : public IPaymentStrategy {
    string email;
public:
    PayPalPayment(string mail) : email(mail) {}
    void pay(double amount) override {
        cout << "Оплата " << amount << " тенге через PayPal: " << email << endl;
    }
};

// Реализация оплаты криптовалютой
class CryptoPayment : public IPaymentStrategy {
    string walletAddress;
public:
    CryptoPayment(string address) : walletAddress(address) {}
    void pay(double amount) override {
        cout << "Оплата " << amount << " тенге с помощью криптовалютного кошелька: " << walletAddress << endl;
    }
};

// Контекст — использует выбранную стратегию
class PaymentContext {
    unique_ptr<IPaymentStrategy> strategy;
public:
    void setStrategy(IPaymentStrategy* s) {
        strategy.reset(s);
    }

    void checkout(double amount) {
        if (strategy)
            strategy->pay(amount);
        else
            cout << "Способ оплаты не выбран!" << endl;
    }
};

// Главная программа
int main() {
    setlocale(LC_ALL, "Russian");
    PaymentContext context;
    int choice;
    double amount;

    cout << "=== Система оплаты ===" << endl;
    cout << "Введите сумму: ";
    cin >> amount;

    cout << "\nВыберите способ оплаты:\n";
    cout << "1. Банковская карта\n";
    cout << "2. PayPal\n";
    cout << "3. Криптовалюта\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
        case 1:
            context.setStrategy(new CreditCardPayment("1234-5678-9012"));
            break;
        case 2:
            context.setStrategy(new PayPalPayment("user@example.com"));
            break;
        case 3:
            context.setStrategy(new CryptoPayment("0xABC123XYZ"));
            break;
        default:
            cout << "Неверный выбор!" << endl;
            return 0;
    }

    cout << endl;
    context.checkout(amount);

    return 0;
}
