#ifndef SMALL_VECTOR_07092017_GASPARYANMOSES
#define SMALL_VECTOR_07092017_GASPARYANMOSES

#include <iostream>

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

	void clean(){
		delete[] data_;
		data_ = nullptr;
		N_ = 0;
	}

	SmallVector() noexcept {
		#if SMALLVECTOR_DEBUG
		std::cout << "\tempty constructor" << std::endl;
		#endif
	}
	explicit SmallVector(size_t N) : N_(N){
		data_ = new ValType[N_];
		for(size_t i=0; i < N_; ++i)
			data_[i] = 0;
		#if SMALLVECTOR_DEBUG
		std::cout << "\tusual constructor" << std::endl;
		#endif
	}
	SmallVector(const SmallVector& rhs) : N_(rhs.N_){
		#if SMALLVECTOR_DEBUG
		std::cout << "\tcopy constructor" << std::endl;
		#endif

		data_ = new ValType[N_];
		for(size_t i=0; i < N_; ++i)
			data_[i] = rhs.data_[i];
	}
	SmallVector(SmallVector&& rhs) noexcept : N_(rhs.N_) {
		#if SMALLVECTOR_DEBUG
		std::cout << "\tcopy&& constructor" << std::endl;
		#endif

		data_ = rhs.data_;
		rhs.data_ = nullptr;
		rhs.N_ = 0;
	}
	~SmallVector(){
		clean();
		#if SMALLVECTOR_DEBUG
		std::cout << "\tdestructor" << std::endl;
		#endif
	}

	SmallVector& operator=(const SmallVector& rhs){
		#if SMALLVECTOR_DEBUG
		std::cout << "\toperator= usual" << std::endl;
		#endif

		if (rhs.data_ != data_){
			delete[] data_;
			N_ = rhs.N_;
			data_ = new ValType[N_];
			memcpy(data_, rhs.data_, N_*sizeof(ValType));
		}
		return *this;
	}

	SmallVector& operator=(SmallVector&& rhs) noexcept {
		#if SMALLVECTOR_DEBUG
		std::cout << "\toperator=&&" << std::endl;
		#endif

		if (rhs.data_ != data_){
			data_ = rhs.data_;
			rhs.data_ = nullptr;
			N_ = rhs.N_;
			rhs.N_ = 0;
		}
		return *this;
	}

	ValType operator[](size_t ind) const { return data_[ind]; }
	ValType& operator[](size_t ind) { return data_[ind]; }
	const size_t& size() const { return N_; }

	void resize(size_t newN){
		if (data_ == nullptr){
			N_ = newN;
			data_ = new ValType[N_];
			for(size_t i=0; i < N_; ++i)
				data_[i] = 0;
		}
		else{
			SmallVector tmp(*this);
			delete[] data_;
			N_ = newN;
			data_ = new ValType[N_];

			if (tmp.N_ < N_){
				for(size_t i=0; i < tmp.N_; ++i)
					data_[i] = tmp.data_[i];
				for(size_t i=tmp.N_; i < N_; ++i)
					data_[i] = 0;
			}
			else{
				for(size_t i=0; i < N_; ++i)
					data_[i] = tmp.data_[i];
			}
		}
	}

	ValType* data() noexcept { return data_; }
	const ValType* data() const noexcept { return data_; }

	SmallVector& operator+=(const SmallVector& rhs){
		#if SMALLVECTOR_DEBUG
		std::cout << "\toperator+= usual" << std::endl;
		#endif

		if (N_ != rhs.N_){
			throw IncompatibleSizesError();
		}

		for(size_t i=0; i < N_; ++i){
			data_[i] += rhs.data_[i];
		}

		return *this;
	}

};

template<typename T>
inline SmallVector<T> operator+(const SmallVector<T>& lhs, const SmallVector<T>& rhs) {
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator+ usual" << std::endl;
	#endif

	SmallVector<T> tmp(lhs);
	return std::move( tmp += rhs );
}

template<typename T>
inline SmallVector<T> operator+(const SmallVector<T>& lhs, SmallVector<T>&& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator+&& in right hand side" << std::endl;
	#endif

	return std::move( rhs += lhs );
}

template<typename T>
inline SmallVector<T> operator+(SmallVector<T>&& lhs, const SmallVector<T>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator+&& in left hand side" << std::endl;
	#endif

	return std::move( lhs += rhs );
}

template<typename T>
inline SmallVector<T> operator+(SmallVector<T>&& lhs, SmallVector<T>&& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator+&& in left and right hand side" << std::endl;
	#endif

	return std::move( lhs += rhs );
}

template<typename T>
inline std::ostream& operator<<(std::ostream& s, const SmallVector<T>& vec){
	s << '[';
	if (vec.size() > 0){
		for(size_t i=0; i < vec.size()-1; ++i){
			s << ' ' << static_cast<int>(vec[i]) << ',';
		}
		s << ' ' << static_cast<int>(vec[vec.size()-1]);
	}
	s << ']';
	return s;
}

#endif // SMALL_VECTOR_07092017_GASPARYANMOSES
