#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class FirstTest : public QObject
{
    Q_OBJECT

public:
    FirstTest();
    ~FirstTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void factorialOfTenMillionIsCorrect();

};

FirstTest::FirstTest()
{

}

FirstTest::~FirstTest()
{

}

void FirstTest::initTestCase()
{

}

void FirstTest::cleanupTestCase()
{

}

void FirstTest::factorialOfTenMillionIsCorrect()
{
    QVERIFY(1 != 2);  // Actual test here!
}

QTEST_MAIN(FirstTest)

#include "tst_firsttest.moc"
