#ifndef uuid_guard_92cee95a_183c6a8e_a298a3fe_cf2b30e1
#define uuid_guard_92cee95a_183c6a8e_a298a3fe_cf2b30e1

#include <iostream>
#include <memory>
#include <string>

#include <keyboard.h>

namespace koa_2020{

class Arduino{
public:
	bool listen(std::shared_ptr<std::istream> socket_);
	void update_keyboard(Keyboard& keyboard);
private:
	std::shared_ptr<std::istream> socket;
};

}

#endif // uuid_guard_92cee95a_183c6a8e_a298a3fe_cf2b30e1
