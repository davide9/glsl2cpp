#pragma once

#include "Swizzler.h"
#include "Util.h"

namespace glsl2cpp {

namespace Details {

template<typename T, size_t N>
struct SwizzlerFactory
{
	template<size_t... Indices>
	struct SwizzlerType
	{
		using type = ::glsl2cpp::Details::Swizzler<Vector_Def_t<T, sizeof...(Indices)>, T, N, Indices...>;
	};

	template<size_t x>
	struct SwizzlerType<x>
	{
		using type = T;
	};
};

template<typename T, size_t N, template<size_t...> class SwizzlerT = SwizzlerFactory<T, N>::SwizzlerType>
struct VectorBase
{
	T myData[N];
};

template<typename T, template<size_t...> class SwizzlerT>
struct VectorBase<T, 1, SwizzlerT>
{
	template<size_t... Indices>
	using Swizzler = typename SwizzlerT<Indices...>::type;

    ~VectorBase() {
        for (auto& data : myData) data.T::~T();
    }

    VectorBase() : myData{} {}

	union
	{
		T myData[1];

		struct
		{
			Swizzler<0> x;
		};

		struct
		{
			Swizzler<0> r;
		};

		struct
		{
			Swizzler<0> s;
		};

		Swizzler<0, 0> xx;
		Swizzler<0, 0, 0> xxx;
		Swizzler<0, 0, 0, 0> xxxx;
	};
};

template<typename T, template<size_t...> class SwizzlerT>
struct VectorBase<T, 2, SwizzlerT>
{
	template<size_t... Indices>
	using Swizzler = typename SwizzlerT<Indices...>::type;

    ~VectorBase() {
        for (auto& data : myData) data.T::~T();
    }
    VectorBase() : myData{} {}


	union
	{
		T myData[2];

		struct
		{
			Swizzler<0> x;
			Swizzler<1> y;
		};

		struct
		{
			Swizzler<0> r;
			Swizzler<1> g;
		};

		struct
		{
			Swizzler<0> s;
			Swizzler<1> t;
		};

		Swizzler<0, 0> xx, ss, uu;
		Swizzler<0, 1> xy, st, uv;

		Swizzler<1, 0> yx, ts, vu;
		Swizzler<1, 1> yy, tt, vv;

		Swizzler<0, 0, 0> xxx, sss, uuu;
		Swizzler<0, 0, 1> xxy, sst, uuv;
		Swizzler<0, 1, 0> xyx, sts, uvu;
		Swizzler<0, 1, 1> xyy, stt, uvv;

		Swizzler<1, 0, 0> yxx, tss, vuu;
		Swizzler<1, 0, 1> yxy, tst, vuv;
		Swizzler<1, 1, 0> yyx, tts, vvu;
		Swizzler<1, 1, 1> yyy, ttt, vvv;

		Swizzler<0, 0, 0, 0> xxxx, ssss, uuuu;
		Swizzler<0, 0, 1, 0> xxyx, ssts, uuvu;
		Swizzler<0, 1, 0, 0> xyxx, stss, uvuu;
		Swizzler<0, 1, 1, 0> xyyx, stts, uvvu;
		Swizzler<1, 0, 0, 0> yxxx, tsss, vuuu;
		Swizzler<1, 0, 1, 0> yxyx, tsts, vuvu;
		Swizzler<1, 1, 0, 0> yyxx, ttss, vvuu;
		Swizzler<1, 1, 1, 0> yyyx, ttts, vvvu;

		Swizzler<0, 0, 0, 1> xxxy, ssst, uuuv;
		Swizzler<0, 0, 1, 1> xxyy, sstt, uuvv;
		Swizzler<0, 1, 0, 1> xyxy, stst, uvuv;
		Swizzler<0, 1, 1, 1> xyyy, sttt, uvvv;
		Swizzler<1, 0, 0, 1> yxxy, tsst, vuuv;
		Swizzler<1, 0, 1, 1> yxyy, tstt, vuvv;
		Swizzler<1, 1, 0, 1> yyxy, ttst, vvuv;
		Swizzler<1, 1, 1, 1> yyyy, tttt, vvvv;
	};
};

template<typename T, template<size_t...> class SwizzlerT>
struct VectorBase<T, 3, SwizzlerT>
{
	template<size_t... Indices>
	using Swizzler = typename SwizzlerT<Indices...>::type;

    ~VectorBase() {
        for (auto& data : myData) data.T::~T();
    }
    VectorBase() : myData{} {}

	union
	{
		T myData[3];

		struct
		{
			Swizzler<0> x;
			Swizzler<1> y;
			Swizzler<2> z;
		};

		struct
		{
			Swizzler<0> r;
			Swizzler<1> g;
			Swizzler<2> b;
		};

		struct
		{
			Swizzler<0> s;
			Swizzler<1> t;
			Swizzler<2> p;
		};

		Swizzler<0, 0> xx, rr, ss;
		Swizzler<0, 1> xy, rg, st;
		Swizzler<0, 2> xz, rb, sp;

		Swizzler<1, 0> yx, gr, ts;
		Swizzler<1, 1> yy, gg, tt;
		Swizzler<1, 2> yz, gb, tp;

		Swizzler<2, 0> zx, br, ps;
		Swizzler<2, 1> zy, bg, pt;
		Swizzler<2, 2> zz, bb, pp;

		Swizzler<0, 0, 0> xxx, rrr, sss;
		Swizzler<0, 0, 1> xxy, rrg, sst;
		Swizzler<0, 0, 2> xxz, rrb, ssp;
		Swizzler<0, 1, 0> xyx, rgr, sts;
		Swizzler<0, 1, 1> xyy, rgg, stt;
		Swizzler<0, 1, 2> xyz, rgb, stp;
		Swizzler<0, 2, 0> xzx, rbr, sps;
		Swizzler<0, 2, 1> xzy, rbg, spt;
		Swizzler<0, 2, 2> xzz, rbb, spp;

		Swizzler<1, 0, 0> yxx, grr, tss;
		Swizzler<1, 0, 1> yxy, grg, tst;
		Swizzler<1, 0, 2> yxz, grb, tsp;
		Swizzler<1, 1, 0> yyx, ggr, tts;
		Swizzler<1, 1, 1> yyy, ggg, ttt;
		Swizzler<1, 1, 2> yyz, ggb, ttp;
		Swizzler<1, 2, 0> yzx, gbr, tps;
		Swizzler<1, 2, 1> yzy, gbg, tpt;
		Swizzler<1, 2, 2> yzz, gbb, tpp;

		Swizzler<2, 0, 0> zxx, brr, pss;
		Swizzler<2, 0, 1> zxy, brg, pst;
		Swizzler<2, 0, 2> zxz, brb, psp;
		Swizzler<2, 1, 0> zyx, bgr, pts;
		Swizzler<2, 1, 1> zyy, bgg, ptt;
		Swizzler<2, 1, 2> zyz, bgb, ptp;
		Swizzler<2, 2, 0> zzx, bbr, pps;
		Swizzler<2, 2, 1> zzy, bbg, ppt;
		Swizzler<2, 2, 2> zzz, bbb, ppp;

		Swizzler<0, 0, 0, 0> xxxx, rrrr, ssss;
		Swizzler<0, 0, 0, 1> xxxy, rrrg, ssst;
		Swizzler<0, 0, 0, 2> xxxz, rrrb, sssp;
		Swizzler<0, 0, 1, 0> xxyx, rrgr, ssts;
		Swizzler<0, 0, 1, 1> xxyy, rrgg, sstt;
		Swizzler<0, 0, 1, 2> xxyz, rrgb, sstp;
		Swizzler<0, 0, 2, 0> xxzx, rrbr, ssps;
		Swizzler<0, 0, 2, 1> xxzy, rrbg, sspt;
		Swizzler<0, 0, 2, 2> xxzz, rrbb, sspp;
		Swizzler<0, 1, 0, 0> xyxx, rgrr, stss;
		Swizzler<0, 1, 0, 1> xyxy, rgrg, stst;
		Swizzler<0, 1, 0, 2> xyxz, rgrb, stsp;
		Swizzler<0, 1, 1, 0> xyyx, rggr, stts;
		Swizzler<0, 1, 1, 1> xyyy, rggg, sttt;
		Swizzler<0, 1, 1, 2> xyyz, rggb, sttp;
		Swizzler<0, 1, 2, 0> xyzx, rgbr, stps;
		Swizzler<0, 1, 2, 1> xyzy, rgbg, stpt;
		Swizzler<0, 1, 2, 2> xyzz, rgbb, stpp;
		Swizzler<0, 2, 0, 0> xzxx, rbrr, spss;
		Swizzler<0, 2, 0, 1> xzxy, rbrg, spst;
		Swizzler<0, 2, 0, 2> xzxz, rbrb, spsp;
		Swizzler<0, 2, 1, 0> xzyx, rbgr, spts;
		Swizzler<0, 2, 1, 1> xzyy, rbgg, sptt;
		Swizzler<0, 2, 1, 2> xzyz, rbgb, sptp;
		Swizzler<0, 2, 2, 0> xzzx, rbbr, spps;
		Swizzler<0, 2, 2, 1> xzzy, rbbg, sppt;
		Swizzler<0, 2, 2, 2> xzzz, rbbb, sppp;

		Swizzler<1, 0, 0, 0> yxxx, grrr, tsss;
		Swizzler<1, 0, 0, 1> yxxy, grrg, tsst;
		Swizzler<1, 0, 0, 2> yxxz, grrb, tssp;
		Swizzler<1, 0, 1, 0> yxyx, grgr, tsts;
		Swizzler<1, 0, 1, 1> yxyy, grgg, tstt;
		Swizzler<1, 0, 1, 2> yxyz, grgb, tstp;
		Swizzler<1, 0, 2, 0> yxzx, grbr, tsps;
		Swizzler<1, 0, 2, 1> yxzy, grbg, tspt;
		Swizzler<1, 0, 2, 2> yxzz, grbb, tspp;
		Swizzler<1, 1, 0, 0> yyxx, ggrr, ttss;
		Swizzler<1, 1, 0, 1> yyxy, ggrg, ttst;
		Swizzler<1, 1, 0, 2> yyxz, ggrb, ttsp;
		Swizzler<1, 1, 1, 0> yyyx, gggr, ttts;
		Swizzler<1, 1, 1, 1> yyyy, gggg, tttt;
		Swizzler<1, 1, 1, 2> yyyz, gggb, tttp;
		Swizzler<1, 1, 2, 0> yyzx, ggbr, ttps;
		Swizzler<1, 1, 2, 1> yyzy, ggbg, ttpt;
		Swizzler<1, 1, 2, 2> yyzz, ggbb, ttpp;
		Swizzler<1, 2, 0, 0> yzxx, gbrr, tpss;
		Swizzler<1, 2, 0, 1> yzxy, gbrg, tpst;
		Swizzler<1, 2, 0, 2> yzxz, gbrb, tpsp;
		Swizzler<1, 2, 1, 0> yzyx, gbgr, tpts;
		Swizzler<1, 2, 1, 1> yzyy, gbgg, tptt;
		Swizzler<1, 2, 1, 2> yzyz, gbgb, tptp;
		Swizzler<1, 2, 2, 0> yzzx, gbbr, tpps;
		Swizzler<1, 2, 2, 1> yzzy, gbbg, tppt;
		Swizzler<1, 2, 2, 2> yzzz, gbbb, tppp;

		Swizzler<2, 0, 0, 0> zxxx, brrr, psss;
		Swizzler<2, 0, 0, 1> zxxy, brrg, psst;
		Swizzler<2, 0, 0, 2> zxxz, brrb, pssp;
		Swizzler<2, 0, 1, 0> zxyx, brgr, psts;
		Swizzler<2, 0, 1, 1> zxyy, brgg, pstt;
		Swizzler<2, 0, 1, 2> zxyz, brgb, pstp;
		Swizzler<2, 0, 2, 0> zxzx, brbr, psps;
		Swizzler<2, 0, 2, 1> zxzy, brbg, pspt;
		Swizzler<2, 0, 2, 2> zxzz, brbb, pspp;
		Swizzler<2, 1, 0, 0> zyxx, bgrr, ptss;
		Swizzler<2, 1, 0, 1> zyxy, bgrg, ptst;
		Swizzler<2, 1, 0, 2> zyxz, bgrb, ptsp;
		Swizzler<2, 1, 1, 0> zyyx, bggr, ptts;
		Swizzler<2, 1, 1, 1> zyyy, bggg, pttt;
		Swizzler<2, 1, 1, 2> zyyz, bggb, pttp;
		Swizzler<2, 1, 2, 0> zyzx, bgbr, ptps;
		Swizzler<2, 1, 2, 1> zyzy, bgbg, ptpt;
		Swizzler<2, 1, 2, 2> zyzz, bgbb, ptpp;
		Swizzler<2, 2, 0, 0> zzxx, bbrr, ppss;
		Swizzler<2, 2, 0, 1> zzxy, bbrg, ppst;
		Swizzler<2, 2, 0, 2> zzxz, bbrb, ppsp;
		Swizzler<2, 2, 1, 0> zzyx, bbgr, ppts;
		Swizzler<2, 2, 1, 1> zzyy, bbgg, pptt;
		Swizzler<2, 2, 1, 2> zzyz, bbgb, pptp;
		Swizzler<2, 2, 2, 0> zzzx, bbbr, ppps;
		Swizzler<2, 2, 2, 1> zzzy, bbbg, pppt;
		Swizzler<2, 2, 2, 2> zzzz, bbbb, pppp;
	};
};

template<typename T, template<size_t...> class SwizzlerT>
struct VectorBase<T, 4, SwizzlerT>
{
	template<size_t... Indices>
	using Swizzler = typename SwizzlerT<Indices...>::type;

    ~VectorBase() {
        for (auto& data : myData) data.T::~T();
    }
    VectorBase() : myData{} {}

	union
	{
		T myData[4];

		struct
		{
			Swizzler<0> x;
			Swizzler<1> y;
			Swizzler<2> z;
			Swizzler<3> w;
		};

		struct
		{
			Swizzler<0> r;
			Swizzler<1> g;
			Swizzler<2> b;
			Swizzler<3> a;
		};

		struct
		{
			Swizzler<0> s;
			Swizzler<1> t;
			Swizzler<2> p;
			Swizzler<3> q;
		};

		Swizzler<0, 0> xx, rr, ss;
		Swizzler<0, 1> xy, rg, st;
		Swizzler<0, 2> xz, rb, sp;
		Swizzler<0, 3> xw, ra, sq;

		Swizzler<1, 0> yx, gr, ts;
		Swizzler<1, 1> yy, gg, tt;
		Swizzler<1, 2> yz, gb, tp;
		Swizzler<1, 3> yw, ga, tq;

		Swizzler<2, 0> zx, br, ps;
		Swizzler<2, 1> zy, bg, pt;
		Swizzler<2, 2> zz, bb, pp;
		Swizzler<2, 3> zw, ba, pq;

		Swizzler<3, 0> wx, ar, qs;
		Swizzler<3, 1> wy, ag, qt;
		Swizzler<3, 2> wz, ab, qp;
		Swizzler<3, 3> ww, aa, qq;

		Swizzler<0, 0, 0> xxx, rrr, sss;
		Swizzler<0, 0, 1> xxy, rrg, sst;
		Swizzler<0, 0, 2> xxz, rrb, ssp;
		Swizzler<0, 0, 3> xxw, rra, ssq;
		Swizzler<0, 1, 0> xyx, rgr, sts;
		Swizzler<0, 1, 1> xyy, rgg, stt;
		Swizzler<0, 1, 2> xyz, rgb, stp;
		Swizzler<0, 1, 3> xyw, rga, stq;
		Swizzler<0, 2, 0> xzx, rbr, sps;
		Swizzler<0, 2, 1> xzy, rbg, spt;
		Swizzler<0, 2, 2> xzz, rbb, spp;
		Swizzler<0, 2, 3> xzw, rba, spq;
		Swizzler<0, 3, 0> xwx, rar, sqs;
		Swizzler<0, 3, 1> xwy, rag, sqt;
		Swizzler<0, 3, 2> xwz, rab, sqp;
		Swizzler<0, 3, 3> xww, raa, sqq;

		Swizzler<1, 0, 0> yxx, grr, tss;
		Swizzler<1, 0, 1> yxy, grg, tst;
		Swizzler<1, 0, 2> yxz, grb, tsp;
		Swizzler<1, 0, 3> yxw, gra, tsq;
		Swizzler<1, 1, 0> yyx, ggr, tts;
		Swizzler<1, 1, 1> yyy, ggg, ttt;
		Swizzler<1, 1, 2> yyz, ggb, ttp;
		Swizzler<1, 1, 3> yyw, gga, ttq;
		Swizzler<1, 2, 0> yzx, gbr, tps;
		Swizzler<1, 2, 1> yzy, gbg, tpt;
		Swizzler<1, 2, 2> yzz, gbb, tpp;
		Swizzler<1, 2, 3> yzw, gba, tpq;
		Swizzler<1, 3, 0> ywx, gar, tqs;
		Swizzler<1, 3, 1> ywy, gag, tqt;
		Swizzler<1, 3, 2> ywz, gab, tqp;
		Swizzler<1, 3, 3> yww, gaa, tqq;

		Swizzler<2, 0, 0> zxx, brr, pss;
		Swizzler<2, 0, 1> zxy, brg, pst;
		Swizzler<2, 0, 2> zxz, brb, psp;
		Swizzler<2, 0, 3> zxw, bra, psq;
		Swizzler<2, 1, 0> zyx, bgr, pts;
		Swizzler<2, 1, 1> zyy, bgg, ptt;
		Swizzler<2, 1, 2> zyz, bgb, ptp;
		Swizzler<2, 1, 3> zyw, bga, ptq;
		Swizzler<2, 2, 0> zzx, bbr, pps;
		Swizzler<2, 2, 1> zzy, bbg, ppt;
		Swizzler<2, 2, 2> zzz, bbb, ppp;
		Swizzler<2, 2, 3> zzw, bba, ppq;
		Swizzler<2, 3, 0> zwx, bar, pqs;
		Swizzler<2, 3, 1> zwy, bag, pqt;
		Swizzler<2, 3, 2> zwz, bab, pqp;
		Swizzler<2, 3, 3> zww, baa, pqq;

		Swizzler<3, 0, 0> wxx, arr, qss;
		Swizzler<3, 0, 1> wxy, arg, qst;
		Swizzler<3, 0, 2> wxz, arb, qsp;
		Swizzler<3, 0, 3> wxw, ara, qsq;
		Swizzler<3, 1, 0> wyx, agr, qts;
		Swizzler<3, 1, 1> wyy, agg, qtt;
		Swizzler<3, 1, 2> wyz, agb, qtp;
		Swizzler<3, 1, 3> wyw, aga, qtq;
		Swizzler<3, 2, 0> wzx, abr, qps;
		Swizzler<3, 2, 1> wzy, abg, qpt;
		Swizzler<3, 2, 2> wzz, abb, qpp;
		Swizzler<3, 2, 3> wzw, aba, qpq;
		Swizzler<3, 3, 0> wwx, aar, qqs;
		Swizzler<3, 3, 1> wwy, aag, qqt;
		Swizzler<3, 3, 2> wwz, aab, qqp;
		Swizzler<3, 3, 3> www, aaa, qqq;

		Swizzler<0, 0, 0, 0> xxxx, rrrr, ssss;
		Swizzler<0, 0, 0, 1> xxxy, rrrg, ssst;
		Swizzler<0, 0, 0, 2> xxxz, rrrb, sssp;
		Swizzler<0, 0, 0, 3> xxxw, rrra, sssq;
		Swizzler<0, 0, 1, 0> xxyx, rrgr, ssts;
		Swizzler<0, 0, 1, 1> xxyy, rrgg, sstt;
		Swizzler<0, 0, 1, 2> xxyz, rrgb, sstp;
		Swizzler<0, 0, 1, 3> xxyw, rrga, sstq;
		Swizzler<0, 0, 2, 0> xxzx, rrbr, ssps;
		Swizzler<0, 0, 2, 1> xxzy, rrbg, sspt;
		Swizzler<0, 0, 2, 2> xxzz, rrbb, sspp;
		Swizzler<0, 0, 2, 3> xxzw, rrba, sspq;
		Swizzler<0, 0, 3, 0> xxwx, rrar, ssqs;
		Swizzler<0, 0, 3, 1> xxwy, rrag, ssqt;
		Swizzler<0, 0, 3, 2> xxwz, rrab, ssqp;
		Swizzler<0, 0, 3, 3> xxww, rraa, ssqq;
		Swizzler<0, 1, 0, 0> xyxx, rgrr, stss;
		Swizzler<0, 1, 0, 1> xyxy, rgrg, stst;
		Swizzler<0, 1, 0, 2> xyxz, rgrb, stsp;
		Swizzler<0, 1, 0, 3> xyxw, rgra, stsq;
		Swizzler<0, 1, 1, 0> xyyx, rggr, stts;
		Swizzler<0, 1, 1, 1> xyyy, rggg, sttt;
		Swizzler<0, 1, 1, 2> xyyz, rggb, sttp;
		Swizzler<0, 1, 1, 3> xyyw, rgga, sttq;
		Swizzler<0, 1, 2, 0> xyzx, rgbr, stps;
		Swizzler<0, 1, 2, 1> xyzy, rgbg, stpt;
		Swizzler<0, 1, 2, 2> xyzz, rgbb, stpp;
		Swizzler<0, 1, 2, 3> xyzw, rgba, stpq;
		Swizzler<0, 1, 3, 0> xywx, rgar, stqs;
		Swizzler<0, 1, 3, 1> xywy, rgag, stqt;
		Swizzler<0, 1, 3, 2> xywz, rgab, stqp;
		Swizzler<0, 1, 3, 3> xyww, rgaa, stqq;
		Swizzler<0, 2, 0, 0> xzxx, rbrr, spss;
		Swizzler<0, 2, 0, 1> xzxy, rbrg, spst;
		Swizzler<0, 2, 0, 2> xzxz, rbrb, spsp;
		Swizzler<0, 2, 0, 3> xzxw, rbra, spsq;
		Swizzler<0, 2, 1, 0> xzyx, rbgr, spts;
		Swizzler<0, 2, 1, 1> xzyy, rbgg, sptt;
		Swizzler<0, 2, 1, 2> xzyz, rbgb, sptp;
		Swizzler<0, 2, 1, 3> xzyw, rbga, sptq;
		Swizzler<0, 2, 2, 0> xzzx, rbbr, spps;
		Swizzler<0, 2, 2, 1> xzzy, rbbg, sppt;
		Swizzler<0, 2, 2, 2> xzzz, rbbb, sppp;
		Swizzler<0, 2, 2, 3> xzzw, rbba, sppq;
		Swizzler<0, 2, 3, 0> xzwx, rbar, spqs;
		Swizzler<0, 2, 3, 1> xzwy, rbag, spqt;
		Swizzler<0, 2, 3, 2> xzwz, rbab, spqp;
		Swizzler<0, 2, 3, 3> xzww, rbaa, spqq;
		Swizzler<0, 3, 0, 0> xwxx, rarr, sqss;
		Swizzler<0, 3, 0, 1> xwxy, rarg, sqst;
		Swizzler<0, 3, 0, 2> xwxz, rarb, sqsp;
		Swizzler<0, 3, 0, 3> xwxw, rara, sqsq;
		Swizzler<0, 3, 1, 0> xwyx, ragr, sqts;
		Swizzler<0, 3, 1, 1> xwyy, ragg, sqtt;
		Swizzler<0, 3, 1, 2> xwyz, ragb, sqtp;
		Swizzler<0, 3, 1, 3> xwyw, raga, sqtq;
		Swizzler<0, 3, 2, 0> xwzx, rabr, sqps;
		Swizzler<0, 3, 2, 1> xwzy, rabg, sqpt;
		Swizzler<0, 3, 2, 2> xwzz, rabb, sqpp;
		Swizzler<0, 3, 2, 3> xwzw, raba, sqpq;
		Swizzler<0, 3, 3, 0> xwwx, raar, sqqs;
		Swizzler<0, 3, 3, 1> xwwy, raag, sqqt;
		Swizzler<0, 3, 3, 2> xwwz, raab, sqqp;
		Swizzler<0, 3, 3, 3> xwww, raaa, sqqq;

		Swizzler<1, 0, 0, 0> yxxx, grrr, tsss;
		Swizzler<1, 0, 0, 1> yxxy, grrg, tsst;
		Swizzler<1, 0, 0, 2> yxxz, grrb, tssp;
		Swizzler<1, 0, 0, 3> yxxw, grra, tssq;
		Swizzler<1, 0, 1, 0> yxyx, grgr, tsts;
		Swizzler<1, 0, 1, 1> yxyy, grgg, tstt;
		Swizzler<1, 0, 1, 2> yxyz, grgb, tstp;
		Swizzler<1, 0, 1, 3> yxyw, grga, tstq;
		Swizzler<1, 0, 2, 0> yxzx, grbr, tsps;
		Swizzler<1, 0, 2, 1> yxzy, grbg, tspt;
		Swizzler<1, 0, 2, 2> yxzz, grbb, tspp;
		Swizzler<1, 0, 2, 3> yxzw, grba, tspq;
		Swizzler<1, 0, 3, 0> yxwx, grar, tsqs;
		Swizzler<1, 0, 3, 1> yxwy, grag, tsqt;
		Swizzler<1, 0, 3, 2> yxwz, grab, tsqp;
		Swizzler<1, 0, 3, 3> yxww, graa, tsqq;
		Swizzler<1, 1, 0, 0> yyxx, ggrr, ttss;
		Swizzler<1, 1, 0, 1> yyxy, ggrg, ttst;
		Swizzler<1, 1, 0, 2> yyxz, ggrb, ttsp;
		Swizzler<1, 1, 0, 3> yyxw, ggra, ttsq;
		Swizzler<1, 1, 1, 0> yyyx, gggr, ttts;
		Swizzler<1, 1, 1, 1> yyyy, gggg, tttt;
		Swizzler<1, 1, 1, 2> yyyz, gggb, tttp;
		Swizzler<1, 1, 1, 3> yyyw, ggga, tttq;
		Swizzler<1, 1, 2, 0> yyzx, ggbr, ttps;
		Swizzler<1, 1, 2, 1> yyzy, ggbg, ttpt;
		Swizzler<1, 1, 2, 2> yyzz, ggbb, ttpp;
		Swizzler<1, 1, 2, 3> yyzw, ggba, ttpq;
		Swizzler<1, 1, 3, 0> yywx, ggar, ttqs;
		Swizzler<1, 1, 3, 1> yywy, ggag, ttqt;
		Swizzler<1, 1, 3, 2> yywz, ggab, ttqp;
		Swizzler<1, 1, 3, 3> yyww, ggaa, ttqq;
		Swizzler<1, 2, 0, 0> yzxx, gbrr, tpss;
		Swizzler<1, 2, 0, 1> yzxy, gbrg, tpst;
		Swizzler<1, 2, 0, 2> yzxz, gbrb, tpsp;
		Swizzler<1, 2, 0, 3> yzxw, gbra, tpsq;
		Swizzler<1, 2, 1, 0> yzyx, gbgr, tpts;
		Swizzler<1, 2, 1, 1> yzyy, gbgg, tptt;
		Swizzler<1, 2, 1, 2> yzyz, gbgb, tptp;
		Swizzler<1, 2, 1, 3> yzyw, gbga, tptq;
		Swizzler<1, 2, 2, 0> yzzx, gbbr, tpps;
		Swizzler<1, 2, 2, 1> yzzy, gbbg, tppt;
		Swizzler<1, 2, 2, 2> yzzz, gbbb, tppp;
		Swizzler<1, 2, 2, 3> yzzw, gbba, tppq;
		Swizzler<1, 2, 3, 0> yzwx, gbar, tpqs;
		Swizzler<1, 2, 3, 1> yzwy, gbag, tpqt;
		Swizzler<1, 2, 3, 2> yzwz, gbab, tpqp;
		Swizzler<1, 2, 3, 3> yzww, gbaa, tpqq;
		Swizzler<1, 3, 0, 0> ywxx, garr, tqss;
		Swizzler<1, 3, 0, 1> ywxy, garg, tqst;
		Swizzler<1, 3, 0, 2> ywxz, garb, tqsp;
		Swizzler<1, 3, 0, 3> ywxw, gara, tqsq;
		Swizzler<1, 3, 1, 0> ywyx, gagr, tqts;
		Swizzler<1, 3, 1, 1> ywyy, gagg, tqtt;
		Swizzler<1, 3, 1, 2> ywyz, gagb, tqtp;
		Swizzler<1, 3, 1, 3> ywyw, gaga, tqtq;
		Swizzler<1, 3, 2, 0> ywzx, gabr, tqps;
		Swizzler<1, 3, 2, 1> ywzy, gabg, tqpt;
		Swizzler<1, 3, 2, 2> ywzz, gabb, tqpp;
		Swizzler<1, 3, 2, 3> ywzw, gaba, tqpq;
		Swizzler<1, 3, 3, 0> ywwx, gaar, tqqs;
		Swizzler<1, 3, 3, 1> ywwy, gaag, tqqt;
		Swizzler<1, 3, 3, 2> ywwz, gaab, tqqp;
		Swizzler<1, 3, 3, 3> ywww, gaaa, tqqq;

		Swizzler<2, 0, 0, 0> zxxx, brrr, psss;
		Swizzler<2, 0, 0, 1> zxxy, brrg, psst;
		Swizzler<2, 0, 0, 2> zxxz, brrb, pssp;
		Swizzler<2, 0, 0, 3> zxxw, brra, pssq;
		Swizzler<2, 0, 1, 0> zxyx, brgr, psts;
		Swizzler<2, 0, 1, 1> zxyy, brgg, pstt;
		Swizzler<2, 0, 1, 2> zxyz, brgb, pstp;
		Swizzler<2, 0, 1, 3> zxyw, brga, pstq;
		Swizzler<2, 0, 2, 0> zxzx, brbr, psps;
		Swizzler<2, 0, 2, 1> zxzy, brbg, pspt;
		Swizzler<2, 0, 2, 2> zxzz, brbb, pspp;
		Swizzler<2, 0, 2, 3> zxzw, brba, pspq;
		Swizzler<2, 0, 3, 0> zxwx, brar, psqs;
		Swizzler<2, 0, 3, 1> zxwy, brag, psqt;
		Swizzler<2, 0, 3, 2> zxwz, brab, psqp;
		Swizzler<2, 0, 3, 3> zxww, braa, psqq;
		Swizzler<2, 1, 0, 0> zyxx, bgrr, ptss;
		Swizzler<2, 1, 0, 1> zyxy, bgrg, ptst;
		Swizzler<2, 1, 0, 2> zyxz, bgrb, ptsp;
		Swizzler<2, 1, 0, 3> zyxw, bgra, ptsq;
		Swizzler<2, 1, 1, 0> zyyx, bggr, ptts;
		Swizzler<2, 1, 1, 1> zyyy, bggg, pttt;
		Swizzler<2, 1, 1, 2> zyyz, bggb, pttp;
		Swizzler<2, 1, 1, 3> zyyw, bgga, pttq;
		Swizzler<2, 1, 2, 0> zyzx, bgbr, ptps;
		Swizzler<2, 1, 2, 1> zyzy, bgbg, ptpt;
		Swizzler<2, 1, 2, 2> zyzz, bgbb, ptpp;
		Swizzler<2, 1, 2, 3> zyzw, bgba, ptpq;
		Swizzler<2, 1, 3, 0> zywx, bgar, ptqs;
		Swizzler<2, 1, 3, 1> zywy, bgag, ptqt;
		Swizzler<2, 1, 3, 2> zywz, bgab, ptqp;
		Swizzler<2, 1, 3, 3> zyww, bgaa, ptqq;
		Swizzler<2, 2, 0, 0> zzxx, bbrr, ppss;
		Swizzler<2, 2, 0, 1> zzxy, bbrg, ppst;
		Swizzler<2, 2, 0, 2> zzxz, bbrb, ppsp;
		Swizzler<2, 2, 0, 3> zzxw, bbra, ppsq;
		Swizzler<2, 2, 1, 0> zzyx, bbgr, ppts;
		Swizzler<2, 2, 1, 1> zzyy, bbgg, pptt;
		Swizzler<2, 2, 1, 2> zzyz, bbgb, pptp;
		Swizzler<2, 2, 1, 3> zzyw, bbga, pptq;
		Swizzler<2, 2, 2, 0> zzzx, bbbr, ppps;
		Swizzler<2, 2, 2, 1> zzzy, bbbg, pppt;
		Swizzler<2, 2, 2, 2> zzzz, bbbb, pppp;
		Swizzler<2, 2, 2, 3> zzzw, bbba, pppq;
		Swizzler<2, 2, 3, 0> zzwx, bbar, ppqs;
		Swizzler<2, 2, 3, 1> zzwy, bbag, ppqt;
		Swizzler<2, 2, 3, 2> zzwz, bbab, ppqp;
		Swizzler<2, 2, 3, 3> zzww, bbaa, ppqq;
		Swizzler<2, 3, 0, 0> zwxx, barr, pqss;
		Swizzler<2, 3, 0, 1> zwxy, barg, pqst;
		Swizzler<2, 3, 0, 2> zwxz, barb, pqsp;
		Swizzler<2, 3, 0, 3> zwxw, bara, pqsq;
		Swizzler<2, 3, 1, 0> zwyx, bagr, pqts;
		Swizzler<2, 3, 1, 1> zwyy, bagg, pqtt;
		Swizzler<2, 3, 1, 2> zwyz, bagb, pqtp;
		Swizzler<2, 3, 1, 3> zwyw, baga, pqtq;
		Swizzler<2, 3, 2, 0> zwzx, babr, pqps;
		Swizzler<2, 3, 2, 1> zwzy, babg, pqpt;
		Swizzler<2, 3, 2, 2> zwzz, babb, pqpp;
		Swizzler<2, 3, 2, 3> zwzw, baba, pqpq;
		Swizzler<2, 3, 3, 0> zwwx, baar, pqqs;
		Swizzler<2, 3, 3, 1> zwwy, baag, pqqt;
		Swizzler<2, 3, 3, 2> zwwz, baab, pqqp;
		Swizzler<2, 3, 3, 3> zwww, baaa, pqqq;

		Swizzler<3, 0, 0, 0> wxxx, arrr, qsss;
		Swizzler<3, 0, 0, 1> wxxy, arrg, qsst;
		Swizzler<3, 0, 0, 2> wxxz, arrb, qssp;
		Swizzler<3, 0, 0, 3> wxxw, arra, qssq;
		Swizzler<3, 0, 1, 0> wxyx, argr, qsts;
		Swizzler<3, 0, 1, 1> wxyy, argg, qstt;
		Swizzler<3, 0, 1, 2> wxyz, argb, qstp;
		Swizzler<3, 0, 1, 3> wxyw, arga, qstq;
		Swizzler<3, 0, 2, 0> wxzx, arbr, qsps;
		Swizzler<3, 0, 2, 1> wxzy, arbg, qspt;
		Swizzler<3, 0, 2, 2> wxzz, arbb, qspp;
		Swizzler<3, 0, 2, 3> wxzw, arba, qspq;
		Swizzler<3, 0, 3, 0> wxwx, arar, qsqs;
		Swizzler<3, 0, 3, 1> wxwy, arag, qsqt;
		Swizzler<3, 0, 3, 2> wxwz, arab, qsqp;
		Swizzler<3, 0, 3, 3> wxww, araa, qsqq;
		Swizzler<3, 1, 0, 0> wyxx, agrr, qtss;
		Swizzler<3, 1, 0, 1> wyxy, agrg, qtst;
		Swizzler<3, 1, 0, 2> wyxz, agrb, qtsp;
		Swizzler<3, 1, 0, 3> wyxw, agra, qtsq;
		Swizzler<3, 1, 1, 0> wyyx, aggr, qtts;
		Swizzler<3, 1, 1, 1> wyyy, aggg, qttt;
		Swizzler<3, 1, 1, 2> wyyz, aggb, qttp;
		Swizzler<3, 1, 1, 3> wyyw, agga, qttq;
		Swizzler<3, 1, 2, 0> wyzx, agbr, qtps;
		Swizzler<3, 1, 2, 1> wyzy, agbg, qtpt;
		Swizzler<3, 1, 2, 2> wyzz, agbb, qtpp;
		Swizzler<3, 1, 2, 3> wyzw, agba, qtpq;
		Swizzler<3, 1, 3, 0> wywx, agar, qtqs;
		Swizzler<3, 1, 3, 1> wywy, agag, qtqt;
		Swizzler<3, 1, 3, 2> wywz, agab, qtqp;
		Swizzler<3, 1, 3, 3> wyww, agaa, qtqq;
		Swizzler<3, 2, 0, 0> wzxx, abrr, qpss;
		Swizzler<3, 2, 0, 1> wzxy, abrg, qpst;
		Swizzler<3, 2, 0, 2> wzxz, abrb, qpsp;
		Swizzler<3, 2, 0, 3> wzxw, abra, qpsq;
		Swizzler<3, 2, 1, 0> wzyx, abgr, qpts;
		Swizzler<3, 2, 1, 1> wzyy, abgg, qptt;
		Swizzler<3, 2, 1, 2> wzyz, abgb, qptp;
		Swizzler<3, 2, 1, 3> wzyw, abga, qptq;
		Swizzler<3, 2, 2, 0> wzzx, abbr, qpps;
		Swizzler<3, 2, 2, 1> wzzy, abbg, qppt;
		Swizzler<3, 2, 2, 2> wzzz, abbb, qppp;
		Swizzler<3, 2, 2, 3> wzzw, abba, qppq;
		Swizzler<3, 2, 3, 0> wzwx, abar, qpqs;
		Swizzler<3, 2, 3, 1> wzwy, abag, qpqt;
		Swizzler<3, 2, 3, 2> wzwz, abab, qpqp;
		Swizzler<3, 2, 3, 3> wzww, abaa, qpqq;
		Swizzler<3, 3, 0, 0> wwxx, aarr, qqss;
		Swizzler<3, 3, 0, 1> wwxy, aarg, qqst;
		Swizzler<3, 3, 0, 2> wwxz, aarb, qqsp;
		Swizzler<3, 3, 0, 3> wwxw, aara, qqsq;
		Swizzler<3, 3, 1, 0> wwyx, aagr, qqts;
		Swizzler<3, 3, 1, 1> wwyy, aagg, qqtt;
		Swizzler<3, 3, 1, 2> wwyz, aagb, qqtp;
		Swizzler<3, 3, 1, 3> wwyw, aaga, qqtq;
		Swizzler<3, 3, 2, 0> wwzx, aabr, qqps;
		Swizzler<3, 3, 2, 1> wwzy, aabg, qqpt;
		Swizzler<3, 3, 2, 2> wwzz, aabb, qqpp;
		Swizzler<3, 3, 2, 3> wwzw, aaba, qqpq;
		Swizzler<3, 3, 3, 0> wwwx, aaar, qqqs;
		Swizzler<3, 3, 3, 1> wwwy, aaag, qqqt;
		Swizzler<3, 3, 3, 2> wwwz, aaab, qqqp;
		Swizzler<3, 3, 3, 3> wwww, aaaa, qqqq;
	};
};

}
}
