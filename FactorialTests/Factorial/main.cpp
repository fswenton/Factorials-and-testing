#include <QCoreApplication>
#include <QElapsedTimer>
#include <QRunnable>
#include <QThreadPool>

#include <iostream>
#include <list>

using namespace std;

class Factorializer : public QRunnable {
public:
    static const quint64 mod;

    quint64 k0, k1, value;
    bool finished;

    Factorializer(quint64 _k0, quint64 _k1):k0(_k0),k1(_k1),value(1),finished(false) {
        setAutoDelete(false);
    }

    void run() {
        for (quint64 k = k0; k <= k1; ++k)
            value = (value * k) % Factorializer::mod;
        finished = true;
    }
};

const quint64 Factorializer::mod = 4294967291ull;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QElapsedTimer timer; timer.start();

    quint64 n = 1000000000ull, value = 1;

#if 0
    for (quint64 k = 1; k <= n; ++k)
        value = (value * k) % Factorializer::mod;
#else
    quint64 blockSize = 1000000;
    unsigned int maxThreads = 8;

    list<Factorializer *> running, onDeck;
    for (quint64 k = 1; k <= n; ) {
        quint64 k0 = k, k1 = k+blockSize-1;
        if (k1 > n) k1 = n;
        onDeck.push_back(new Factorializer(k0, k1));
        k = k1+1;
    }

    while (!(running.empty() && onDeck.empty())) {
        // Check for finished workers
        for (auto iThread = running.begin(); iThread != running.end(); )
            if ((*iThread)->finished) {
                value = (value * (*iThread)->value) % Factorializer::mod;
                delete *iThread;
                running.erase(iThread++);
            } else
                ++iThread;

       while (running.size() < maxThreads && !onDeck.empty()) {
            Factorializer *thread = onDeck.front(); onDeck.pop_front();
            QThreadPool::globalInstance()->start(thread);
            running.push_back(thread);
       }

       // QApplication::processEvents();
    }
#endif

    cout << value << ", obtained in " << timer.elapsed()/1000.0 << " seconds\n";

    return a.exec();
}
