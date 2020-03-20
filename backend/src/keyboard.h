#ifndef uuid_guard_0140fd2e_352bd0d3_38d23936_ddf2fa03
#define uuid_guard_0140fd2e_352bd0d3_38d23936_ddf2fa03

#include <map>
#include <vector>

#include <key_state.h>

namespace koa_2020{

class Keyboard{
public:
	void set_num_keys(int num_keys);

	const std::vector<Key_state>& get_states() const;

	bool update_states(const std::map<int, Key_state>& updates);
private:
	std::vector<Key_state> state;
};

}

#endif // uuid_guard_0140fd2e_352bd0d3_38d23936_ddf2fa03
