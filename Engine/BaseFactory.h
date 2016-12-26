#ifndef __BASEFACTORY_H__
#define __BASEFACTORY_H__
#include <type_traits>

template <typename TClass>
class BaseFactory
{
public:

	BaseFactory() {}

	virtual ~BaseFactory() {}

	virtual TClass* GetObject(int id) const = 0;

	template<typename TConcrete> 
	TConcrete* GetObject(int id) const
	{
		static_assert(std::is_base_of<TClass, TConcrete>::value, "Return class is not a subclass of the factory");

		return static_cast<TConcrete*>(GetObject(id));
	}
};

#endif // __BASEFACTORY_H__
