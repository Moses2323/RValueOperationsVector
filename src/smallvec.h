#ifndef SMALL_VECTOR_07092017_GASPARYANMOSES
#define SMALL_VECTOR_07092017_GASPARYANMOSES

#define SMALLVECTOR_DEBUG 1

template<typename T>
class SmallVector{
public:
	using ValType = T;
private:
	size_t N_ {0};
	ValType* data_ {nullptr};

public:
	class IncompatibleSizesError{};

	void clean();

	SmallVector() noexcept;
	explicit SmallVector(size_t N);
	SmallVector(const SmallVector& rhs);
	SmallVector(SmallVector&& rhs) noexcept;
	~SmallVector();

	SmallVector& operator=(const SmallVector& rhs);

	SmallVector& operator=(SmallVector&& rhs) noexcept;

	ValType operator[](size_t ind) const { return data_[ind]; }
	ValType& operator[](size_t ind) { return data_[ind]; }
	const size_t& size() const noexcept { return N_; }

	void resize(size_t newN);

	ValType* data() noexcept { return data_; }
	const ValType* data() const noexcept { return data_; }

	SmallVector& operator+=(const SmallVector& rhs);
};

template<typename T>
SmallVector<T> operator+(const SmallVector<T>& lhs, const SmallVector<T>& rhs);

template<typename T>
SmallVector<T> operator+(const SmallVector<T>& lhs, SmallVector<T>&& rhs);

template<typename T>
SmallVector<T> operator+(SmallVector<T>&& lhs, const SmallVector<T>& rhs);

template<typename T>
SmallVector<T> operator+(SmallVector<T>&& lhs, SmallVector<T>&& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& s, const SmallVector<T>& vec);

#include "smallvec_rz.h"

#endif // SMALL_VECTOR_07092017_GASPARYANMOSES
