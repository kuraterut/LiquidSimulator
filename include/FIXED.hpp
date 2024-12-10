//
// Created by Семён on 04.12.2024.
//

#ifndef FLUID_PROJECT_FIXED_H
#define FLUID_PROJECT_FIXED_H

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <tuple>
#include <algorithm>

//template <uint8_t N, uint8_t K>
//class Fixed {
//    static_assert(N > K, "N must be greater than K");
//    using value_t = std::conditional_t<
//    N <= 8, int8_t,
//    std::conditional_t<
//            N <= 16, int16_t,
//            std::conditional_t<
//            N <= 32, int32_t,
//            std::conditional_t<N == 64, int64_t, void>>>>;
//
//    static constexpr int32_t scale = 1 << K;
//
//    value_t v;
//
//    template <uint8_t N2, uint8_t K2>
//    static constexpr value_t convert_value(value_t value) {
//        if constexpr (K > K2) {
//            return value << (K - K2);
//        } else if constexpr (K < K2) {
//            return value >> (K2 - K);
//        } else {
//            return value;
//        }
//    }
//
//public:
//    constexpr Fixed(int v = 0) : v(v << K) {}
//    constexpr Fixed(float f) : v(static_cast<value_t>(f * scale)) {}
//    constexpr Fixed(double f) : v(static_cast<value_t>(f * scale)) {}
//
//    static constexpr Fixed from_raw(value_t x) {
//        Fixed ret;
//        ret.v = x;
//        return ret;
//    }
//
//    constexpr auto operator<=>(const Fixed&) const = default;
//    constexpr bool operator==(const Fixed&) const = default;
//
//    Fixed operator+(Fixed other) const { return from_raw(v + other.v); }
//    Fixed operator-(Fixed other) const { return from_raw(v - other.v); }
//    Fixed operator*(Fixed other) const {
//        return from_raw(static_cast<int64_t>(v) * other.v / scale);
//    }
//    Fixed operator/(Fixed other) const {
//        return from_raw(static_cast<int64_t>(v) * scale / other.v);
//    }
//
//    Fixed& operator+=(Fixed other) { return *this = *this + other; }
//    Fixed& operator-=(Fixed other) { return *this = *this - other; }
//    Fixed& operator*=(Fixed other) { return *this = *this * other; }
//    Fixed& operator/=(Fixed other) { return *this = *this / other; }
//
//    Fixed operator-() const { return from_raw(-v); }
//
//    constexpr Fixed abs() const { return from_raw(v < 0 ? -v : v); }
//
//    template <uint8_t N2, uint8_t K2>
//    constexpr Fixed(const Fixed<N2, K2>& other)
//            : v(convert_value<N2, K2>(other.raw_value())) {}
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed operator+(const Fixed<N2, K2>& other) const {
//        return *this + Fixed(other);
//    }
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed operator-(const Fixed<N2, K2>& other) const {
//        return *this - Fixed(other);
//    }
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed operator*(const Fixed<N2, K2>& other) const {
//        return *this * Fixed(other);
//    }
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed operator/(const Fixed<N2, K2>& other) const {
//        return *this / Fixed(other);
//    }
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed& operator+=(const Fixed<N2, K2>& other) {
//        return *this = *this + other;
//    }
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed& operator-=(const Fixed<N2, K2>& other) {
//        return *this = *this - other;
//    }
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed& operator*=(const Fixed<N2, K2>& other) {
//        return *this = *this * other;
//    }
//
//    template <uint8_t N2, uint8_t K2>
//    Fixed& operator/=(const Fixed<N2, K2>& other) {
//        return *this = *this / other;
//    }
//
//    constexpr value_t raw_value() const { return v; }
//
//    friend std::ostream& operator<<(std::ostream& out, const Fixed& x) {
//        return out << static_cast<double>(x.v) / scale;
//    }
//
//    // Перегрузка операторов для float и double
//    friend Fixed operator+(const Fixed& lhs, float rhs) {
//        return lhs + Fixed(rhs);
//    }
//    friend Fixed operator+(float lhs, const Fixed& rhs) {
//        return Fixed(lhs) + rhs;
//    }
//
//    friend Fixed operator-(const Fixed& lhs, float rhs) {
//        return lhs - Fixed(rhs);
//    }
//    friend Fixed operator-(float lhs, const Fixed& rhs) {
//        return Fixed(lhs) - rhs;
//    }
//
//    friend Fixed operator*(const Fixed& lhs, float rhs) {
//        return lhs * Fixed(rhs);
//    }
//    friend Fixed operator*(float lhs, const Fixed& rhs) {
//        return Fixed(lhs) * rhs;
//    }
//
//    friend Fixed operator/(const Fixed& lhs, float rhs) {
//        return lhs / Fixed(rhs);
//    }
//    friend Fixed operator/(float lhs, const Fixed& rhs) {
//        return Fixed(lhs) / rhs;
//    }
//
//    friend Fixed operator+(const Fixed& lhs, double rhs) {
//        return lhs + Fixed(rhs);
//    }
//    friend Fixed operator+(double lhs, const Fixed& rhs) {
//        return Fixed(lhs) + rhs;
//    }
//
//    friend Fixed operator-(const Fixed& lhs, double rhs) {
//        return lhs - Fixed(rhs);
//    }
//    friend Fixed operator-(double lhs, const Fixed& rhs) {
//        return Fixed(lhs) - rhs;
//    }
//
//    friend Fixed operator*(const Fixed& lhs, double rhs) {
//        return lhs * Fixed(rhs);
//    }
//    friend Fixed operator*(double lhs, const Fixed& rhs) {
//        return Fixed(lhs) * rhs;
//    }
//
//    friend Fixed operator/(const Fixed& lhs, double rhs) {
//        return lhs / Fixed(rhs);
//    }
//    friend Fixed operator/(double lhs, const Fixed& rhs) {
//        return Fixed(lhs) / rhs;
//    }
//
//    Fixed& operator+=(float rhs) {
//        return *this = *this + Fixed(rhs);
//    }
//    Fixed& operator-=(float rhs) {
//        return *this = *this - Fixed(rhs);
//    }
//    Fixed& operator*=(float rhs) {
//        return *this = *this * Fixed(rhs);
//    }
//    Fixed& operator/=(float rhs) {
//        return *this = *this / Fixed(rhs);
//    }
//
//    Fixed& operator+=(double rhs) {
//        return *this = *this + Fixed(rhs);
//    }
//    Fixed& operator-=(double rhs) {
//        return *this = *this - Fixed(rhs);
//    }
//    Fixed& operator*=(double rhs) {
//        return *this = *this * Fixed(rhs);
//    }
//    Fixed& operator/=(double rhs) {
//        return *this = *this / Fixed(rhs);
//    }
//
//    friend float& operator+=(float& lhs, const Fixed& rhs) {
//        lhs += static_cast<float>(rhs);
//        return lhs;
//    }
//    friend float& operator-=(float& lhs, const Fixed& rhs) {
//        lhs -= static_cast<float>(rhs);
//        return lhs;
//    }
//    friend float& operator*=(float& lhs, const Fixed& rhs) {
//        lhs *= static_cast<float>(rhs);
//        return lhs;
//    }
//    friend float& operator/=(float& lhs, const Fixed& rhs) {
//        lhs /= static_cast<float>(rhs);
//        return lhs;
//    }
//
//    friend double& operator+=(double& lhs, const Fixed& rhs) {
//        lhs += static_cast<double>(rhs);
//        return lhs;
//    }
//    friend double& operator-=(double& lhs, const Fixed& rhs) {
//        lhs -= static_cast<double>(rhs);
//        return lhs;
//    }
//    friend double& operator*=(double& lhs, const Fixed& rhs) {
//        lhs *= static_cast<double>(rhs);
//        return lhs;
//    }
//    friend double& operator/=(double& lhs, const Fixed& rhs) {
//        lhs /= static_cast<double>(rhs);
//        return lhs;
//    }
//};


template <uint8_t N, uint8_t K>
class Fixed {
    static_assert(N > K, "N must be greater than K");
    using value_t = std::conditional_t<
            N <= 8, int8_t,
            std::conditional_t<
                    N <= 16, int16_t,
                    std::conditional_t<
                            N <= 32, int32_t,
                            std::conditional_t<N == 64, int64_t, void>>>>;

    static constexpr value_t scale = 1 << K;

    value_t v;

    template <uint8_t N2, uint8_t K2>
    static constexpr value_t convert_value(value_t value) {
        if constexpr (K > K2) {
            return value << (K - K2);
        } else if constexpr (K < K2) {
            return value >> (K2 - K);
        } else {
            return value;
        }
    }


public:
    constexpr static uint8_t n = N;
    constexpr static uint8_t k = K;

    constexpr Fixed(int v = 0) : v(v << K) {}
    constexpr Fixed(float f) : v(static_cast<value_t>(f * scale)) {}
    constexpr Fixed(double f) : v(static_cast<value_t>(f * scale)) {}

    explicit operator double() const {
        return static_cast<double>(v) / scale;
    }

    explicit operator float () const {
        return static_cast<float>(v) / scale;
    }

    static constexpr Fixed from_raw(value_t x) {
        Fixed ret;
        ret.v = x;
        return ret;
    }

    constexpr auto operator<=>(const Fixed&) const = default;
    constexpr bool operator==(const Fixed&) const = default;

    Fixed operator+(Fixed other) const { return from_raw(v + other.v); }
    Fixed operator-(Fixed other) const { return from_raw(v - other.v); }
    Fixed operator*(Fixed other) const {
        return from_raw(static_cast<int64_t>(v) * other.v / scale);
    }
    Fixed operator/(Fixed other) const {
        return from_raw(static_cast<int64_t>(v) * scale / other.v);
    }

    Fixed& operator+=(Fixed other) { return *this = *this + other; }
    Fixed& operator-=(Fixed other) { return *this = *this - other; }
    Fixed& operator*=(Fixed other) { return *this = *this * other; }
    Fixed& operator/=(Fixed other) { return *this = *this / other; }

    Fixed operator-() const { return from_raw(-v); }

    constexpr Fixed abs() const { return from_raw(v < 0 ? -v : v); }

    template <uint8_t N2, uint8_t K2>
    constexpr Fixed(const Fixed<N2, K2>& other)
            : v(convert_value<N2, K2>(other.raw_value())) {}

    template <uint8_t N2, uint8_t K2>
    Fixed operator+(const Fixed<N2, K2>& other) const {
        return *this + Fixed(other);
    }

    template <uint8_t N2, uint8_t K2>
    Fixed operator-(const Fixed<N2, K2>& other) const {
        return *this - Fixed(other);
    }

    template <uint8_t N2, uint8_t K2>
    Fixed operator*(const Fixed<N2, K2>& other) const {
        return *this * Fixed(other);
    }

    template <uint8_t N2, uint8_t K2>
    Fixed operator/(const Fixed<N2, K2>& other) const {
        return *this / Fixed(other);
    }

    template <uint8_t N2, uint8_t K2>
    Fixed& operator+=(const Fixed<N2, K2>& other) {
        return *this = *this + other;
    }

    template <uint8_t N2, uint8_t K2>
    Fixed& operator-=(const Fixed<N2, K2>& other) {
        return *this = *this - other;
    }

    template <uint8_t N2, uint8_t K2>
    Fixed& operator*=(const Fixed<N2, K2>& other) {
        return *this = *this * other;
    }

    template <uint8_t N2, uint8_t K2>
    Fixed& operator/=(const Fixed<N2, K2>& other) {
        return *this = *this / other;
    }

    constexpr value_t raw_value() const { return v; }

    friend std::ostream& operator<<(std::ostream& out, const Fixed& x) {
        return out << static_cast<double>(x.v) / scale;
    }



    friend Fixed operator+(Fixed& f, double val){
        return f + Fixed(val);
    }
    friend Fixed operator+(double val, Fixed& f){
        return f + Fixed(val);
    }


    friend Fixed operator-(Fixed& f, double val){
        return f - Fixed(val);
    }
    friend Fixed operator-(double val, Fixed& f){
        return f - Fixed(val);
    }


    friend Fixed operator*(Fixed& f, double val){
        return f * Fixed(val);
    }
    friend Fixed operator*(double val, Fixed& f){
        return f * Fixed(val);
    }

    friend Fixed operator/(Fixed& f, double val){
        return f / Fixed(val);
    }
    friend Fixed operator/(double val, Fixed& f){
        return f / Fixed(val);
    }


    friend double& operator+=(double& lhs, const Fixed& rhs) {
        lhs += static_cast<double>(rhs.v) / scale;
        return lhs;
    }
    friend double& operator-=(double& lhs, const Fixed& rhs) {
        lhs -= static_cast<double>(rhs.v) / scale;;
        return lhs;
    }
    friend double& operator*=(double& lhs, const Fixed& rhs) {
        lhs *= static_cast<double>(rhs.v) / scale;;
        return lhs;
    }
    friend double& operator/=(double& lhs, const Fixed& rhs) {
        lhs /= static_cast<double>(rhs.v) / scale;;
        return lhs;
    }


    friend float& operator+=(float& lhs, const Fixed& rhs) {
        lhs += static_cast<float>(rhs.v) / scale;
        return lhs;
    }
    friend float& operator-=(float& lhs, const Fixed& rhs) {
        lhs -= static_cast<float>(rhs.v) / scale;;
        return lhs;
    }
    friend float& operator*=(float& lhs, const Fixed& rhs) {
        lhs *= static_cast<float>(rhs.v) / scale;;
        return lhs;
    }
    friend float& operator/=(float& lhs, const Fixed& rhs) {
        lhs /= static_cast<float>(rhs.v) / scale;;
        return lhs;
    }


    Fixed& operator+=(double rhs) {
        return *this = *this + Fixed(rhs);
    }
    Fixed& operator-=(double rhs) {
        return *this = *this - Fixed(rhs);
    }
    Fixed& operator*=(double rhs) {
        return *this = *this * Fixed(rhs);
    }
    Fixed& operator/=(double rhs) {
        return *this = *this / Fixed(rhs);
    }
};

#endif //FLUID_PROJECT_FIXED_H