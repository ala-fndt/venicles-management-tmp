#ifndef IREFRESHABLE_HPP
#define IREFRESHABLE_HPP

class IRefreshable {
public:
  virtual void refresh() = 0;
  virtual ~IRefreshable() = default;
};

#endif // !IREFRESHABLE_HPP
