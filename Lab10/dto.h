#include <string>

using namespace std;

class DTO
{
private:
	string tip;
	int cnt;
public:
	DTO() = default;
	DTO(const string g, int c) :tip{ g }, cnt{ c } {};

	string get_tip() const
	{
		return this->tip;
	}

	int get_cnt() const
	{
		return this->cnt;
	}

	void increment_cnt() noexcept
	{
		cnt++;
	}
};