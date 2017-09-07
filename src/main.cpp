#include <iostream>
#include <string>

#include "smallvec.h"

int main() {
	using std::cout;
	using std::cerr;
	using std::endl;

	size_t N = 7;
	SmallVector<short> vec1(N);
	SmallVector<short> vec2(N);

	for(size_t i=0; i < N; ++i){
		vec1[i] = i;
		vec2[i] = i*10;
	}
	/* TEST FOR FUNCTIONS
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
	*/
	SmallVector<short> vec3(N);
	SmallVector<short> vec4;
	for(size_t i=0; i < vec3.size(); ++i){
		vec3[i] = i/2;
	}

	cout << "STRANGE ARYTHMETICS:" << endl;
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

	return 0;
}
