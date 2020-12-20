//this program is not absolutely right.
#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <unistd.h>
#include <assert.h>
#include "Mutex.h"
using namespace std;
using namespace placeholders;

class Stock
{
public:
  Stock(const string &name) : m_name(name)
  {
    cout << "Stock():" << m_name << endl;
  }
  ~Stock()
  {
    cout << "~Stock():" << m_name << endl;
  }
  const string& key() const
  {
    return m_name;
  }

private:
  string m_name;
};

class Factory : public enable_shared_from_this<Factory>
{
public:
  Factory()
  {}

  shared_ptr<Stock> getStock(const string &key)
  {
    shared_ptr<Stock> sharedStock;
    xuel::MutexGuard guard(m_mutex);
    sharedStock = m_stocks[key].lock();
    if (!sharedStock)
    {
      sharedStock.reset(new Stock(key),
          std::bind(&Factory::deleteCallback, this, _1));
      m_stocks[key] = sharedStock;
    }
    return sharedStock;
  }

  void showMap()
  {
    cout << "allMap: ";
    for (auto m : m_stocks)
    {
      cout << m.first << ",";
    }
    cout << endl;
  }

private:
  void deleteCallback(Stock *pStock)
  {
    cout << "deleteCallback" << endl;
    //if (factory) 
    xuel::MutexGuard guard(m_mutex);
    if (pStock)
    {
      auto it = m_stocks.find(pStock->key());
      assert(it != m_stocks.end());
      if (it->second.expired())
      {
        m_stocks.erase(pStock->key());
      }
    }
    delete pStock;
  }

  map<string, weak_ptr<Stock>> m_stocks;
  xuel::Mutex m_mutex;
};

void longLifeFactory()
{
  shared_ptr<Factory> factory(new Factory);
  {
    shared_ptr<Stock> stockIBM = factory->getStock("IBM");
    shared_ptr<Stock> stockGoogle = factory->getStock("GOOG");
  }
  factory->showMap();
}
void shortLifeFactory()
{
  shared_ptr<Stock> stockIBM;
  {
    shared_ptr<Factory> factory(new Factory);
    stockIBM = factory->getStock("IBM");
    shared_ptr<Stock> stockGoogle = factory->getStock("GOOD");
    factory->showMap();
  }
}

int main()
{
  longLifeFactory();
  //shortLifeFactory(); //not work
  sleep(10);
}
