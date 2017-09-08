#ifndef SMALL_VECTOR_07092017_GASPARYANMOSES
#define SMALL_VECTOR_07092017_GASPARYANMOSES

#define SMALLVECTOR_DEBUG 1

/*! \~russian
 * \brief Класс реализует вектор с арифметическими операциями.
 *
 * Класс является экспериментом с rvalue-ссылками и их использованием
 * в операторах.
 *
 * Схема использования:
 * \code
 *  using std::cout;
 *  using std::endl;
 *
 *  size_t N = 7;
 *  SmallVector<short> vec1(N);
 *  SmallVector<short> vec2(N);
 *
 *  for(size_t i=0; i < N; ++i){
 *      vec1[i] = i;
 *      vec2[i] = i*10;
 *  }
 *  SmallVector<short> vec3(N);
 *  SmallVector<short> vec4;
 *  for(size_t i=0; i < vec3.size(); ++i){
 *      vec3[i] = i/2;
 *  }
 *
 *  cout << "\tSTRANGE ARYTHMETICS:" << endl;
 *  cout << "vec1 = " << vec1 << endl;
 *  cout << "vec2 = " << vec2 << endl;
 *  cout << "vec3 = " << vec3 << endl;
 *  cout << "vec4 = " << vec4 << endl;
 *  vec4 = vec1 + vec2 + vec3;
 *  cout << "vec1 + vec2 + vec3 : " << vec4 << endl;
 * \endcode
 *
 */
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
	SmallVector& operator-=(const SmallVector& rhs);
	template<typename U>
	SmallVector<T>& operator*=(const U& scalar);
	template<typename U>
	SmallVector<T>& operator*=(const SmallVector<U>& rhs);
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
SmallVector<T> operator-(const SmallVector<T>& lhs, const SmallVector<T>& rhs);

template<typename T>
SmallVector<T> operator-(const SmallVector<T>& lhs, SmallVector<T>&& rhs);

template<typename T>
SmallVector<T> operator-(SmallVector<T>&& lhs, const SmallVector<T>& rhs);

template<typename T>
SmallVector<T> operator-(SmallVector<T>&& lhs, SmallVector<T>&& rhs);

template<typename T>
SmallVector<T> operator-(const SmallVector<T>& vec);

template<typename T>
SmallVector<T> operator-(SmallVector<T>&& vec);

template<typename T>
std::ostream& operator<<(std::ostream& s, const SmallVector<T>& vec);

#include "smallvec_rz.h"

#endif // SMALL_VECTOR_07092017_GASPARYANMOSES
