#pragma once

// 2023/7/17
// TypeRich编程思想，用于模块接口的数据类型安全检查
// 定义 mks 单位类型
template <int M, int K, int S>
struct MKSUnitType {
	enum { _metre = M, _kilogram = K, _second = S };
};

// 定义 mks 值类型
template <typename MKSUnitType>
class MKSValueType {
public:
	constexpr explicit MKSValueType(const double magnitude) noexcept : m_magnitude(magnitude) {}
	constexpr double GetMagnitude() const noexcept { return m_magnitude; }

private:
	double m_magnitude{ 0.0 };
};


// 声明常用的物理学类型
using DimensionlessQuantity = MKSValueType<MKSUnitType<0, 0, 0>>;
using Length = MKSValueType<MKSUnitType<1, 0, 0>>;
using Area = MKSValueType<MKSUnitType<2, 0, 0>>;
using Volum = MKSValueType<MKSUnitType<3, 0, 0>>;
using Mass = MKSValueType<MKSUnitType<0, 1, 0>>;
using Time = MKSValueType<MKSUnitType<0, 0, 1>>;
using Speed = MKSValueType<MKSUnitType<1, 0, -1>>;
using Acceleration = MKSValueType<MKSUnitType<1, 0, -2>>;
using Force = MKSValueType<MKSUnitType<1, 1, -2>>;
using Momentum = MKSValueType<MKSUnitType<1, 1, -1>>;

// 定义尾缀
constexpr Speed operator"" _ms(long double magnitude) {
	return Speed(magnitude);
}

constexpr Acceleration operator"" _ms2(long double magnitude) {
	return Acceleration(magnitude);
}

constexpr Time operator"" _s(long double magnitude) {
	return Time(magnitude);
}

constexpr Force operator"" _N(long double magnitude) {
	return Force(magnitude);
}

// 定义运算符
template <int M, int K, int S>
constexpr MKSValueType<MKSUnitType<M, K, S>> operator+ (
	const MKSValueType<MKSUnitType<M, K, S>>& v1,
	const MKSValueType<MKSUnitType<M, K, S>>& v2
	) {
	return MKSValueType<MKSUnitType<M, K, S>>(v1.GetMagnitude() + v2.GetMagnitude());
}

template <int M, int K, int S>
constexpr MKSValueType<MKSUnitType<M, K, S>> operator- (
	const MKSValueType<MKSUnitType<M, K, S>>& v1,
	const MKSValueType<MKSUnitType<M, K, S>>& v2
	) {
	return MKSValueType<MKSUnitType<M, K, S>>(v1.GetMagnitude() - v2.GetMagnitude());
}

template <int M1, int K1, int S1, int M2, int K2, int S2>
constexpr MKSValueType<MKSUnitType<M1 + M2, K1 + K2, S1 + S2>> operator* (
	const MKSValueType<MKSUnitType<M1, K1, S1>>& v1,
	const MKSValueType<MKSUnitType<M2, K2, S2>>& v2
	) {
	return MKSValueType<MKSUnitType<M1 + M2, K1 + K2, S1 + S2>>(v1.GetMagnitude() * v2.GetMagnitude());
}

template <int M1, int K1, int S1, int M2, int K2, int S2>
constexpr MKSValueType<MKSUnitType<M1 - M2, K1 - K2, S1 - S2>> operator/ (
	const MKSValueType<MKSUnitType<M1, K1, S1>>& v1,
	const MKSValueType<MKSUnitType<M2, K2, S2>>& v2
	) {
	return MKSValueType<MKSUnitType<M1 - M2, K1 - K2, S1 - S2>>(v1.GetMagnitude() / v2.GetMagnitude());
}

// 支持不同的单位制
constexpr Mass operator "" _kg(long double magnitude) {
	return Mass(magnitude);
}
constexpr static Mass pound = 0.4535923_kg;
constexpr static Acceleration g = 9.80665_ms2;
constexpr Force operator "" _lbf(long double magnitude) {
	return pound * g * DimensionlessQuantity(magnitude);
}