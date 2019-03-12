#ifndef CZX_NONCOPYABLE_H_190312
#define CZX_NONCOPYABLE_H_190312
class NonCopyable
{
public:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator = (const NonCopyable&) = delete;
	NonCopyable() = default;
};
#endif