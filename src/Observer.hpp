
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

/*
Generally, our UIEntities are observers, and our HAentities are subjects.
We have this specific "interface" inspired by https://refactoring.guru/design-patterns/observer/cpp/example because we don't want
HAEntity to have a direct link to UIEntity. If we do that, then HAEntity would know about lvgl.h which it shouldn't.
*/
class IObserver
{
public:
  virtual ~IObserver(){};
  virtual void uiupdate();
};

class ISubject
{
public:
  virtual ~ISubject(){};
  virtual void attach(IObserver* observer);
  virtual void detach(IObserver* observer);
  virtual void notify();
};

#endif