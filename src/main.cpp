#include "smallvec.h"

#include <iostream>
#include <string>
#include <vector>
#include <valarray>
#include <ctime>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;

void test_usual_functions(){
	cout << "START USUAL FUNCTIONS TEST" << endl;

	size_t N = 7;
	SmallVector<short> vec1(N);
	SmallVector<short> vec2(N);

	for(size_t i=0; i < N; ++i){
		vec1[i] = i;
		vec2[i] = i*10;
	}
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl << endl;

	SmallVector<short> vec3(vec1);
	cout << "vec3 (copy vec1) = " << vec3 << endl;
	cout << "vec1 = " << vec1 << endl << endl;

	SmallVector<short> vec4(std::move(vec3));
	cout << "vec4 (copy&& vec3) = " << vec4 << endl;
	cout << "vec3 = " << vec3 << endl << endl;

	cout << "vec1 += vec2 : " << (vec1 += vec2) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl << endl;

	cout << "vec1 + vec2 : " << vec1 + vec2 << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl << endl;

	vec3.resize(N);
	for(size_t i=0; i < N; ++i){
		vec3[i] = i/2;
	}

	vec4.clean();

	SmallVector<short> vec5(N);
	for(size_t i=0; i < N; ++i){
		vec5[i] = i + 2;
	}
	cout << "vec5 = " << vec5 << endl;
	vec5.resize(N+3);
	cout << "vec5 with resize N+3 = " << vec5 << endl;
	vec5.resize(N/2);
	cout << "vec5 with resize N/2 = " << vec5 << endl;
	vec5.resize(0);
	cout << "vec5 with resize(0) = " << vec5 << endl;

	cout << "END OF USUAL FUNCTIONS TEST" << endl;
}

void test_plus(){
	cout << "START PLUS TEST" << endl;

	size_t N = 7;
	SmallVector<short> vec1(N);
	SmallVector<short> vec2(N);

	for(size_t i=0; i < N; ++i){
		vec1[i] = i;
		vec2[i] = i*10;
	}
	SmallVector<short> vec3(N);
	SmallVector<short> vec4;
	for(size_t i=0; i < vec3.size(); ++i){
		vec3[i] = i/2;
	}

	cout << "\tSTRANGE ARYTHMETICS:" << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	cout << "vec3 = " << vec3 << endl;
	cout << "vec4 = " << vec4 << endl;
	vec4 = vec1 + vec2 + vec3;
	cout << "vec1 + vec2 + vec3 : " << vec4 << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	cout << "vec3 = " << vec3 << endl;
	cout << "vec4 = " << vec4 << endl;
	cout << endl;

	vec4.clean();
	cout << endl;

	vec4 = std::move(std::move(vec1 + vec2) + vec3);
	cout << "std::move(std::move(vec1 + vec2) + vec3) : " << vec4 << endl;
	cout << "END OF PLUS TEST" << endl;
}

void test_unary_minus(){
	cout << "START UNARY MINUS TEST" << endl;

	size_t N = 7;
	SmallVector<int> vec1(N);
	for(size_t i=0; i < vec1.size(); ++i)
		vec1[i] = i*2 + 1;

	cout << "vec1 = " << vec1 << endl;
	cout << "-vec1 = " << -vec1 << endl << endl;

	SmallVector<int> vec2;
	cout << "vec2 = " << vec2 << endl;
	vec2 = -vec1;
	cout << "vec1 = " << vec1 << endl;
	cout << "after vec2 = -vec1 : " << vec2 << endl << endl;

	for(size_t i=0; i < vec2.size(); ++i)
		vec2[i] = i;

	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	vec2 = -std::move(vec1);
	cout << "after vec2 = -std::move(vec1):" << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;

	cout << "END OF UNARY MINUS TEST" << endl;
}

void test_multiply(){
	cout << "START MULTIPLY TEST" << endl;

	size_t N = 7;
	SmallVector<double> vec1(N);
	for(size_t i=0; i < N; ++i)
		vec1[i] = i + 1;

	SmallVector<double> vec2(N);
	for(size_t i=0; i < N ; ++i)
		vec2[i] = 10 - i;

	double aud = 0.1;
	int aui = 5;

	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	cout << "aud = " << aud << endl;
	cout << "aui = " << aui << endl << endl;

	cout << "(vec1 *= aud) : " << (vec1 *= aud) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "aud = " << aud << endl << endl;

	cout << "(vec1 *= aui) : " << (vec1 *= aui) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "aui = " << aui << endl << endl;

	cout << "(vec1 *= vec2) : " << (vec1 *= vec2) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;

	cout << "END OF MULTIPLY TEST" << endl;
}

void test_equal(){
	cout << "START EQUAL TEST" << endl;

	size_t N = 7;
	SmallVector<int> veci(N);
	SmallVector<double> vecd(N);

	for(size_t i=0; i < N; ++i){
		veci[i] = i;
		vecd[i] = i / 10.0;
	}

	cout << "veci = " << veci << endl;
	cout << "vecd = " << vecd << endl << endl;
	cout << "veci == vecd : " << (veci == vecd) << endl;
	cout << "veci = " << veci << endl;
	cout << "vecd = " << vecd << endl << endl;

	cout << "END OF EQUAL TEST" << endl;
}

void test_time(){
	std::cout << "START TIME TEST" << std::endl;
	cout << std::setprecision(10);

	size_t N = 10000000;

	std::valarray<double> val1(N), val2(N), val3(N);
	SmallVector<double> vec1(N), vec2(N), vec3(N);

	long long int t1, t2;
	double time1, time2;

	for(size_t i=0; i < N; ++i){
		val1[i] = i;
		val2[i] = i*0.5;
		val3[i] = i / 2.0;

		vec1[i] = val1[i];
		vec2[i] = val2[i];
		vec3[i] = val3[i];
	}

	t1 = clock();
	val1 += val2;
	val1 *= val3;
	val1 += val2;
	val1 /= val2;
	val1 += val3;
	t2 = clock();
	time1 = static_cast<double>(t2 - t1)/CLOCKS_PER_SEC;
	std::cout << "time val1 += val2 : " << time1 << " sec" << std::endl;

	t1 = clock();
	vec1 += vec2;
	vec1 *= vec3;
	vec1 += vec2;
	vec1 /= vec2;
	vec1 += vec3;
	t2 = clock();
	time2 = static_cast<double>(t2 - t1)/CLOCKS_PER_SEC;
	std::cout << "time vec1 += vec2 : " << time2 << " sec" << std::endl;
	std::cout << "diffTime (time of vec - time of val) : " << time2 - time1 << " sec" << endl << endl;

	// -----------------------------------

	SmallVector<double> vvec1(N), vvec2(N), vvec3(N), vvec4(N);
	std::valarray<double> vval1(N), vval2(N), vval3(N), vval4(N);

	for(size_t i=0; i < N; ++i){
		vval1[i] = i;
		vval2[i] = i*0.5;
		vval3[i] = i / 2.0;
		vval4[i] = i * 2.4;

		vvec1[i] = vval1[i];
		vvec2[i] = vval2[i];
		vvec3[i] = vval3[i];
		vvec4[i] = vval4[i];
	}

	t1 = clock();
	vval1 = vval2 + vval3 + vval4;
	t2 = clock();
	time1 = static_cast<double>(t2 - t1)/CLOCKS_PER_SEC;
	std::cout << "time vval1 = vval2 + vval3 + vval4 : " << time1 << " sec" << std::endl;


	t1 = clock();
	vvec1 = vvec2 + vvec3 + vvec4;
	t2 = clock();
	time2 = static_cast<double>(t2 - t1)/CLOCKS_PER_SEC;
	std::cout << "time vvec1 = vvec2 + vvec3 + vvec4 : " << time2 << " sec" << std::endl;
	std::cout << "diffTime (time of vec - time of val) : " << time2 - time1 << " sec" << endl << endl;

	cout << endl << "END OF TIME TEST" << endl;

	// += with -O0 : valarray faster or equal
	// += with -O3 : valarray slower or equal
}

int main() {
	test_usual_functions();
	cout << "--------------------------------------------------" << endl;
	test_plus();
	cout << "--------------------------------------------------" << endl;
	test_unary_minus();
	cout << "--------------------------------------------------" << endl;
	test_multiply();
	cout << "--------------------------------------------------" << endl;
	test_equal();
	cout << "--------------------------------------------------" << endl;
	test_time();

	return 0;
}
