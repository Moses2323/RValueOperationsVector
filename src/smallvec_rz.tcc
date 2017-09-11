// THIS FILE MUST NOT BE INCLUDED IN PROJECTS!
// FILE CONTAINS ONLY REALISATION OF METHODS IN CLASS SmallVector<T>

#include <cstring>
#include <type_traits>

template<typename T>
void SmallVector<T>::fieldWithZeroIfTrivial(int shift){
	if (std::is_trivial<T>())
		std::memset(data_ + shift, 0, (N_ - shift)*sizeof(T));
}

template<typename T>
inline void SmallVector<T>::clean(){
	delete[] data_;
	data_ = nullptr;
	N_ = 0;
}

template<typename T>
inline SmallVector<T>::SmallVector() noexcept {
	#if SMALLVECTOR_DEBUG
	std::cout << "\tempty constructor" << std::endl;
	#endif
}

template<typename T>
inline SmallVector<T>::SmallVector(size_t N) : N_(N){
	#if SMALLVECTOR_DEBUG
	std::cout << "\tusual constructor" << std::endl;
	#endif
	data_ = new ValType[N_];

	fieldWithZeroIfTrivial();
}

template<typename T>
inline SmallVector<T>::SmallVector(const SmallVector<T>& rhs) : N_(rhs.N_){
	#if SMALLVECTOR_DEBUG
	std::cout << "\tcopy constructor" << std::endl;
	#endif

	data_ = new ValType[N_];
	std::memcpy(data_, rhs.data_, N_*sizeof(ValType));
}

template<typename T>
inline SmallVector<T>::SmallVector(SmallVector<T>&& rhs) noexcept : N_(rhs.N_) {
	#if SMALLVECTOR_DEBUG
	std::cout << "\tcopy&& constructor" << std::endl;
	#endif

	data_ = rhs.data_;
	rhs.data_ = nullptr;
	rhs.N_ = 0;
}

template<typename T>
inline SmallVector<T>::~SmallVector(){
	#if SMALLVECTOR_DEBUG
	std::cout << "\tdestructor" << std::endl;
	#endif
	clean();
}

template<typename T>
inline SmallVector<T>& SmallVector<T>::operator=(const SmallVector<T>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator= usual" << std::endl;
	#endif

	if (rhs.data_ != data_){
		delete[] data_;
		N_ = rhs.N_;
		data_ = new ValType[N_];
		std::memcpy(data_, rhs.data_, N_*sizeof(ValType));
	}
	return *this;
}

template<typename T>
inline SmallVector<T>& SmallVector<T>::operator=(SmallVector<T>&& rhs) noexcept {
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

template<typename T>
inline void SmallVector<T>::resize(size_t newN){
	if (data_ == nullptr){
		if (newN){
			N_ = newN;
			data_ = new ValType[N_];
			fieldWithZeroIfTrivial();
		}
	}
	else{
		if (newN == 0){
			clean();
			return;
		}
		if (newN == N_)
			return;

		SmallVector<T> tmp(std::move(*this));
		N_ = newN;
		data_ = new ValType[N_];

		if (tmp.N_ < N_){
			for(size_t i=0; i < tmp.N_; ++i)
				data_[i] = tmp.data_[i];
			for(size_t i=tmp.N_; i < N_; ++i)
				data_[i] = 0;
			fieldWithZeroIfTrivial(tmp.N_);
		}
		else{
			for(size_t i=0; i < N_; ++i)
				data_[i] = tmp.data_[i];
		}
	}
}

template<typename T>
template<typename U>
inline SmallVector<T>& SmallVector<T>::operator+=(const SmallVector<U>& rhs){
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

template<typename T>
template<typename U>
inline SmallVector<T>& SmallVector<T>::operator-=(const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator-= usual" << std::endl;
	#endif

	if (N_ != rhs.N_){
		throw IncompatibleSizesError();
	}

	for(size_t i=0; i < N_; ++i){
		data_[i] -= rhs.data_[i];
	}

	return *this;
}

template<typename T>
template<typename U>
inline SmallVector<T>& SmallVector<T>::operator*=(const U& scalar){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator*= for scalar" << std::endl;
	#endif

	for(size_t i=0; i < N_; ++i)
		data_[i] *= scalar;
	return *this;
}

template<typename T>
template<typename U>
SmallVector<T>& SmallVector<T>::operator*=(const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator*= usual (for vector)" << std::endl;
	#endif

	if (N_ != rhs.N_){
		throw IncompatibleSizesError();
	}

	for(size_t i=0; i < N_; ++i)
		data_[i] *= rhs.data_[i];
	return *this;
}

template<typename T>
template<typename U>
inline SmallVector<T>& SmallVector<T>::operator/=(const U& scalar){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator/= for scalar" << std::endl;
	#endif

	for(size_t i=0; i < N_; ++i)
		data_[i] /= scalar;
	return *this;
}

template<typename T>
template<typename U>
SmallVector<T>& SmallVector<T>::operator/=(const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator/= usual (for vector)" << std::endl;
	#endif

	if (N_ != rhs.N_){
		throw IncompatibleSizesError();
	}

	for(size_t i=0; i < N_; ++i)
		data_[i] /= rhs.data_[i];
	return *this;
}

// + - * / -------------------------------------------------

template<typename T>
inline SmallVector<T> operator-(const SmallVector<T>& vec){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator- unary usual" << std::endl;
	#endif

	SmallVector<T> tmp(vec);
	for(size_t i=0; i < vec.size(); ++i)
		tmp[i] *= -1;
	return std::move(tmp);
}

template<typename T>
inline SmallVector<T> operator-(SmallVector<T>&& vec){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator- unary&&" << std::endl;
	#endif

	SmallVector<T> tmp(std::move(vec));
	for(size_t i=0; i < tmp.size(); ++i)
		tmp[i] *= -1;
	return std::move(tmp);
}

template<typename T>
inline SmallVector<T> operator-(const SmallVector<T>& lhs, const SmallVector<T>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator- usual" << std::endl;
	#endif

	SmallVector<T> tmp(lhs);
	return std::move( tmp -= rhs );
}

template<typename T>
inline SmallVector<T> operator-(const SmallVector<T>& lhs, SmallVector<T>&& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator-&& in right hand side" << std::endl;
	#endif

	SmallVector<T> tmp(std::move(-std::move(rhs)));
	return std::move( tmp += lhs );
}

template<typename T>
inline SmallVector<T> operator-(SmallVector<T>&& lhs, const SmallVector<T>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator-&& in left hand side" << std::endl;
	#endif

	SmallVector<T> tmp(std::move(lhs));
	return std::move( tmp -= rhs );
}

template<typename T>
inline SmallVector<T> operator-(SmallVector<T>&& lhs, SmallVector<T>&& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator-&& in left and right hand side" << std::endl;
	#endif

	SmallVector<T> tmp(std::move(lhs));
	return std::move( tmp -= rhs );
}

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
inline SmallVector<T> operator*(const SmallVector<T>& lhs, const SmallVector<T>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator* usual" << std::endl;
	#endif

	SmallVector<T> tmp(lhs);
	return std::move( tmp *= rhs );
}

template<typename T>
inline SmallVector<T> operator*(const SmallVector<T>& lhs, SmallVector<T>&& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator*&& in right hand side" << std::endl;
	#endif

	return std::move( rhs *= lhs );
}

template<typename T>
inline SmallVector<T> operator*(SmallVector<T>&& lhs, const SmallVector<T>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator*&& in left hand side" << std::endl;
	#endif

	return std::move( lhs *= rhs );
}

template<typename T>
inline SmallVector<T> operator*(SmallVector<T>&& lhs, SmallVector<T>&& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator*&& in left and right hand side" << std::endl;
	#endif

	return std::move( lhs *= rhs );
}

// == < > <= >= -------------------------------------------------

/*!
 * \brief Operator ==
 * \details Do operator== with all elements of vector.
 * \todo do this function with rvalue-reference and allocator later
 * \param lhs left hand side
 * \param rhs right hand side
 * \return boolean vector
 */
template<typename T, typename U>
SmallVector<bool> operator==(const SmallVector<T>& lhs, const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator== usual" << std::endl;
	#endif

	if (lhs.size() != rhs.size())
		throw typename SmallVector<T>::IncompatibleSizesError();

	SmallVector<bool> res(lhs.size());
	for(size_t i=0; i < lhs.size(); ++i)
		res[i] = (lhs[i] == rhs[i]);

	return std::move( res );
}

template<typename T, typename U>
SmallVector<bool> operator<(const SmallVector<T>& lhs, const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator< usual" << std::endl;
	#endif

	if (lhs.size() != rhs.size())
		throw typename SmallVector<T>::IncompatibleSizesError();

	SmallVector<bool> res(lhs.size());
	for(size_t i=0; i < lhs.size(); ++i)
		res[i] = (lhs[i] < rhs[i]);

	return std::move( res );
}

template<typename T, typename U>
SmallVector<bool> operator>(const SmallVector<T>& lhs, const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator> usual" << std::endl;
	#endif

	if (lhs.size() != rhs.size())
		throw typename SmallVector<T>::IncompatibleSizesError();

	SmallVector<bool> res(lhs.size());
	for(size_t i=0; i < lhs.size(); ++i)
		res[i] = (lhs[i] > rhs[i]);

	return std::move( res );
}

template<typename T, typename U>
SmallVector<bool> operator<=(const SmallVector<T>& lhs, const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator<= usual" << std::endl;
	#endif

	if (lhs.size() != rhs.size())
		throw typename SmallVector<T>::IncompatibleSizesError();

	SmallVector<bool> res(lhs.size());
	for(size_t i=0; i < lhs.size(); ++i)
		res[i] = (lhs[i] <= rhs[i]);

	return std::move( res );
}

template<typename T, typename U>
SmallVector<bool> operator>=(const SmallVector<T>& lhs, const SmallVector<U>& rhs){
	#if SMALLVECTOR_DEBUG
	std::cout << "\toperator< usual" << std::endl;
	#endif

	if (lhs.size() != rhs.size())
		throw typename SmallVector<T>::IncompatibleSizesError();

	SmallVector<bool> res(lhs.size());
	for(size_t i=0; i < lhs.size(); ++i)
		res[i] = (lhs[i] >= rhs[i]);

	return std::move( res );
}

// << -------------------------------------------------

template<typename T>
inline std::ostream& operator<<(std::ostream& s, const SmallVector<T>& vec){
	s << '[';
	if (vec.size() > 0){
		for(size_t i=0; i < vec.size()-1; ++i){
			s << ' ' << vec[i] << ',';
		}
		s << ' ' << vec[vec.size()-1];
	}
	s << ']';
	return s;
}
