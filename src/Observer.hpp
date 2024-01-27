
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
  virtual void uiupdate() = 0;
  virtual ~IObserver(){};
};

class ISubject
{
public:
  virtual void attach(IObserver* observer) = 0;
  virtual void detach(IObserver* observer) = 0;
  virtual void notify() = 0;
  virtual ~ISubject(){};
};

#endif