/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef TQUATERNION_H
#define TQUATERNION_H

#include "TinyVec.h"
#include "TinyMat.h"
#include "Affine.h"

namespace Spr{;

/**	\addtogroup gpLinearAlgebra	*/
//@{
/**	@file TQuaternion.h
	�N�H�[�^�j�I���N���X�̒�`
 */

/**	Quaternion/4�����D3x3�s��̑���ɉ�]��\�����߂Ɏg����D
	4�ϐ��ōςށD��Ԃ�����E�ϕ������₷���D<br>
	TVec3�Ƃ̊|���Z�́C��]�ϊ��ŃI�[�o�[���[�h����Ă���D
*/
template<class ET>
class TQuaternion:public PTM::TVectorBase<4, TVecDesc<TQuaternion<ET>, ET> >{
public:
	typedef TVecDesc<TQuaternion<ET>, ET> desc;
	typedef PTM::TVectorBase<4, desc> base_type;
	///	�p������Ȃ���{�I�ȃ����o�̒�`.	@see ::DEF_TVECTOR_BASIC_MEMBER
	DEF_TVECTOR_BASIC_MEMBER(TQuaternion);
	union{
		ET data[4];
		struct{
			ET w,x,y,z;
		};
	};
	///	�v�f�̃A�N�Z�X
	ET& item_impl(size_t i){ return data[i]; }
	///	�v�f�̃A�N�Z�X
	const ET& item_impl(size_t i) const { return data[i]; }
	///	�X�g���C�h
	size_t stride_impl() const { return 1; }

	///	3�����̕����x�N�g��
	typedef PTM::TSubVector<3, desc> vector_type;
	///@name �ϐ��A�N�Z�X
	//@{
	///	w����
	const element_type& W() const { return w; }
	///	x����
	const element_type& X() const { return x; }
	///	y����
	const element_type& Y() const { return y; }
	///	z����
	const element_type& Z() const { return z; }
	///
	const vector_type& V() const {return this->sub_vector(1,vector_type());}

	///	z����
	element_type& W(){ return w; }
	///	x����
	element_type& X(){ return x; }
	///	y����
	element_type& Y(){ return y; }
	///	z����
	element_type& Z(){ return z; }
	/// 
	vector_type& V() {return this->sub_vector(1,vector_type());}

	/// ��]�x�N�g���D0..PI�͈̔͂ŉ�]�x�N�g����Ԃ��D
	TVec3<ET> RotationHalf() {
		TQuaternion<ET> tmp;
		if (W() < 0) tmp = -*this;
		else tmp = *this;
		TVec3<ET> r;
		if (tmp.W() > 1) tmp.W() = 1;
		ET theta = (ET)( acos(tmp.W()) * 2 );
		r = tmp.sub_vector(1, vector_type());
		ET len = r.norm();
		if (len > 1e-20){
			r = r/len;
		}
		r *= theta;
		return r;
	}
	///	��]�x�N�g��2�D 0..2PI�͈̔͂ŉ�]�x�N�g����Ԃ��D	angle ����֐����ύX
	TVec3<ET> Rotation(){
		//	W() = cos(theta/2) �Ȃ̂�
		TVec3<ET> r;
		if (W() < -1) W() = -1;
		if (W() > 1) W() = 1;
		ET theta = (ET)( acos(W()) * 2 );
		r = this->sub_vector(1, vector_type());
		ET len = r.norm();
		if (len > 1e-20){
			r = r/len;
		}
		r *= theta;
		return r;
	}

	/// ��]��
	TVec3<ET> Axis()const{
		TVec3<ET> r;
		r = sub_vector(1, vector_type());
		ET len = r.norm();
		if (len > 1e-20){
			r = r/len;
		}
		else{	
			// r�̃m������0�Ƃ������Ƃ͉�]�p�x��0�Ƃ������ƂȂ̂ŉ�]���͔C�ӁD
			// 0�x�N�g����Ԃ��킯�ɂ͂����Ȃ��̂�[1 0 0]��Ԃ�
			return TVec3<ET>(1, 0, 0);
		}
		return r;
	}

	/// ��]�p�x (angle�Ɋ֐�����ύX����\��)
	ET Theta()const{
		/// ���l�덷��W��1.0�����ƃG���[����ꍇ������
		double w = W();
		w = std::min(w,  1.0);
		w = std::max(w, -1.0);
		return (ET)( acos(w) * 2 );
	}
	//@}

	///@name �������E�\�z
	//@{
	///	�R���X�g���N�^
	TQuaternion(element_type wi, element_type xi, element_type yi, element_type zi){ W() = wi; X() = xi; Y() = yi; Z() = zi;}
	template <class B>
	void InitDirect(element_type a, const PTM::TVectorBase<3, B> v){
		W() = a; V() = v;
	}
	template <class B>
	void InitDirect(element_type a, const PTM::TVectorBase<4, B> v){
		W() = v[0]; X() = v[1]; Y() = v[2]; Z() = v[3];
	}
	static TQuaternion<ET> Rot(element_type angle, const TVec3<element_type>& axis){
		TQuaternion<ET> quat;
		PTM::init_quaternion(quat, angle, axis);
		return quat;
	}
	static TQuaternion<ET> Rot(element_type angle, char axis){
		TQuaternion<ET> quat;
		PTM::init_quaternion(quat, angle, axis);
		return quat;
	}
	static TQuaternion<ET> Rot(const TVec3<element_type>& rot){
		TQuaternion<ET> quat;
		PTM::init_quaternion(quat, rot);
		return quat;
	}

	//@}
	///����
	void Conjugate() { V() = -V(); }
	///	
	TQuaternion Conjugated() const { TQuaternion rv(*this); rv.Conjugate(); return rv;}
	///�t
	TQuaternion Inv() const { return Conjugated() / this->square(); }

	///��]�s��ϊ�
	template<class AM> void FromMatrix(const AM& m)
	{
		ET tr = m[0][0] + m[1][1] + m[2][2] + 1;
		if (tr > (0.1f)){
			ET s = ET( 0.5/sqrt(tr) );
			W() = ET( 0.25 / s );
			X() = ET( (m[2][1] - m[1][2]) * s );
			Y() = ET( (m[0][2] - m[2][0]) * s );
			Z() = ET( (m[1][0] - m[0][1]) * s );
		}else if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) { 
			ET s = ET(sqrt( 1.0 + m[0][0] - m[1][1] - m[2][2] ) * 2);
			X() = ET(0.25) * s;
			Y() = (m[0][1] + m[1][0]) / s; 
			Z() = (m[0][2] + m[2][0]) / s; 
			W() = (m[1][2] - m[2][1]) / s;
		} else if (m[1][1] > m[2][2]) {
			ET s = ET( sqrt(1.0 + m[1][1] - m[0][0] - m[2][2] ) * 2);
			X() = (m[0][1] + m[1][0] ) / s;
			Y() = ET(0.25) * s;
			Z() = (m[1][2] + m[2][1] ) / s; 
			W() = (m[0][2] - m[2][0] ) / s;
		} else { 
			ET s = ET( sqrt( 1.0 + m[2][2] - m[0][0] - m[1][1] ) * 2); 
			X() = (m[0][2] + m[2][0] ) / s;
			Y() = (m[1][2] + m[2][1] ) / s;
			Z() = ET(0.25) * s;
			W() = (m[1][0] - m[0][1] ) / s;
		}
		this->unitize();
	}
	template<class AM> void ToMatrix(AM& mat) const
	{
		typedef TYPENAME AM::element_type AMET;
		mat[0][0] = AMET( 1.0 - 2.0 * (Y()*Y() + Z()*Z()) );
		mat[1][0] = AMET( 2.0 * (X()*Y() + Z()*W()) );
		mat[2][0] = AMET( 2.0 * (X()*Z() - Y()*W()) );
		mat[0][1] = AMET( 2.0 * (Y()*X() - Z()*W()) );
		mat[1][1] = AMET( 1.0 - 2.0 * (X()*X() + Z()*Z()) );
		mat[2][1] = AMET( 2.0 * (Y()*Z() + X()*W()) );
		mat[0][2] = AMET( 2.0 * (X()*Z() + Y()*W()) );
		mat[1][2] = AMET( 2.0 * (Y()*Z() - X()*W()) );
		mat[2][2] = AMET( 1.0 - 2.0 * (X()*X() + Y()*Y()) );
	}
	///	�I�C���[�p(Y��(heading), Z��(attitude), X��(bank)�̏��̃I�C���[�p)�֕ϊ�
	/*	�I�C���[�p�͊֐߂̏��Ԃɂ���Ă��낢��Ȓ�`������B
		�����ł́AY����Z����X���̏���l���Ă���B
		heading, attitude, bank�̌Ăі��́A�Ԃ��E������Ă���ꍇ��l����ƁA
		�[�������Ǝv���܂��B
	*/
	template <class VET> void ToEuler(TVec3<VET>& v)const{
		ET poleCheck = X()*Y() + Z()*W();
		VET& heading = v[0];
		VET& attitude = v[1];
		VET& bank = v[2];
		if (poleCheck > 0.499){				//	north pole
			heading = 2 * atan2(X(),W());
			bank = 0;
		}else if(poleCheck < -0.499){		//	south pole
			heading = -2 * atan2(X(),W());
			bank = 0;
		}else{
			heading = atan2(2*Y()*W()-2*X()*Z() , 1 - 2*Y()*Y() - 2*Z()*Z());
			attitude = asin(2*X()*Y() + 2*Z()*W());
			bank = atan2(2*X()*W()-2*Y()*Z() , 1 - 2*X()*X() - 2*Z()*Z());
		}
	}
	///	�I�C���[�p(Y��(heading), Z��(attitude), X��(bank)�̏��̃I�C���[�p)����ϊ�
	template <class VET> void FromEuler(const TVec3<VET>& v){
		VET heading = v[0];
		VET attitude = v[1];
		VET bank = v[2];

		ET c1 = cos(heading / 2);
		ET c2 = cos(attitude / 2);
		ET c3 = cos(bank / 2);
		ET s1 = sin(heading / 2);
		ET s2 = sin(attitude / 2);
		ET s3 = sin(bank / 2);
		
		W() = c1*c2*c3 - s1*s2*s3;
		X() = s1*s2*c3 + c1*c2*s3;
		Y() = s1*c2*c3 + c1*s2*s3;
		Z() = c1*s2*c3 - s1*c2*s3;
	}
	///lhs���]����rhs�Ɉ�v������N�E�H�[�^�j�I��
	void RotationArc(const TVec3<ET>& lhs, const TVec3<ET>& rhs){
		TVec3<ET> v0, v1, c;
		ET d, s;
		v0 = lhs.unit();
		v1 = rhs.unit();
		c = PTM::cross(v0, v1);
		d = PTM::dot(v0, v1);
		if(d==-1){
			// lhs��rhs�������΂̌����̂Ƃ��Ƀ[�������N�����Ă����̂�ikko������ɏ��������� (07/08/27)
			W() = 0;
			V() = PTM::cross(v0, (v0==TVec3<ET>(1,0,0) ? TVec3<ET>(0,1,0) : TVec3<ET>(1,0,0))).unit();
		}
		else{
			s = sqrt((1.0 + d) * 2.0);
			W() = s / 2.0;
			V() = c / s;
		}
	}

	///�I�C���[�p�Ŏw�� (FromEuler�Ƃ܂���������)
	void Euler(ET heading, ET attitude, ET bank) {
		ET c1 = cos(heading / 2);
		ET s1 = sin(heading / 2);
		ET c2 = cos(attitude / 2);
		ET s2 = sin(attitude / 2);
		ET c3 = cos(bank / 2);
		ET s3 = sin(bank / 2);
		
		W() = c1*c2*c3 - s1*s2*s3;
		X() = s1*s2*c3 + c1*c2*s3;
		Y() = s1*c2*c3 + c1*s2*s3;
		Z() = c1*s2*c3 - s1*c2*s3;
	}

	/** @brief �p���x����quaternion�̎��Ԕ�����v�Z
		@param w �p���x

		����quaternion�Ɗp���xw����Cquaternion�̎��Ԕ�����v�Z����D
		������w�͉�]���i���[���h�j���W�n���猩����]��i���[�J���j���W�n�̊p���x��
		��]�����W�n�ŕ\�킵����́D
	 */
	TQuaternion<ET> Derivative(const TVec3<ET>& w)const{
		return 0.5 * TQuaternion<ET>(0.0, w.X(), w.Y(), w.Z()) * *this;
	}

	/** @brief �N�E�H�[�^�j�I���̎��Ԕ�������p���x��v�Z
		@param qd quaternion�̎��Ԕ���
		@return �p���x

		����quaternion�Ƃ��̎��Ԕ���qd����p���xw��v�Z����D
		������w�͉�]���i���[���h�j���W�n���猩����]��i���[�J���j���W�n�̊p���x��
		��]�����W�n�ŕ\�킵����́D
	 */
	TVec3<ET> AngularVelocity(const TQuaternion<ET>& qd)const{
		return 2.0 * (qd * Conjugated()).V();
	}

protected:
	///	�R���X�g���N�^
	void set_default(){ W() = 1; X() = 0; Y() = 0; Z() = 0;}
};

///	TQuaternion ���m�̊|���Z�D��]�ϊ��Ƃ��ẮC�����ɂȂ�D
template <class A, class B>
TQuaternion<A> operator*(const TQuaternion<A>& q1, const TQuaternion<B>& q2){
    TQuaternion<A> rv;
	rv.W() = q1.W() * q2.W() - q1.X() * q2.X() - q1.Y() * q2.Y() - q1.Z() * q2.Z();
	rv.X() = q1.W() * q2.X() + q1.X() * q2.W() + q1.Y() * q2.Z() - q1.Z() * q2.Y();
	rv.Y() = q1.W() * q2.Y() + q1.Y() * q2.W() + q1.Z() * q2.X() - q1.X() * q2.Z();
	rv.Z() = q1.W() * q2.Z() + q1.Z() * q2.W() + q1.X() * q2.Y() - q1.Y() * q2.X();
	return rv;
}

///	TQuaternion�Ńx�N�g�����]�D Quaternion * vector * Quaternion^{*} �Ɠ����D
template <class ET, class BD>
inline TYPENAME BD::ret_type operator*(const TQuaternion<ET>& q, const PTM::TVectorBase<3, BD>& v){
	// ����1������0�ł͂Ȃ����H�H�@tazz
	//TQuaternion<ET> qv(1, ET(v[0]), ET(v[1]), ET(v[2]));
	//TYPENAME BD::ret_type r = (q * qv * q.Conjugated()).sub_vector(PTM::TSubVectorDim<1,3>());
	// ���͑�1������0�Ƃ��ēW�J�����R�[�h
	TYPENAME BD::ret_type tmp = q.V() % v;
	TYPENAME BD::ret_type r = (BD::element_type)(q.W()*q.W())*v + (BD::element_type)(2*q.W())*tmp + (BD::element_type)(q.V()*v)*q.V() + q.V()%tmp;
	return r;
}

///	TQuaternion�ōs����]�D TQuaternion * (ex,ey,ez) * TQuaternion.conjugated() �Ɠ����D
template <class ET, class BD>
inline TYPENAME BD::ret_type operator*(const TQuaternion<ET>& q, const PTM::TMatrixBase<3, 3, BD>& m){
	TYPENAME BD::ret_type r;
	for(int i=0; i<3; ++i){
		// ��Ɠ�����0�Ǝv����
		TQuaternion<ET> qv(0, ET(m.col(i)[0]), ET(m.col(i)[1]), ET(m.col(i)[2]));
		r.col(i) = (q * qv * q.Conjugated()).sub_vector(PTM::TSubVectorDim<1,3>());
	}
	return r;
}

///	TQuaternion �̓�ρD
template <class T1, class T2>
inline T1 dot(const TQuaternion<T1>& q1, const TQuaternion<T2>& q2) {
	return q1.X() * q2.X() + q1.Y() * q2.Y() + q1.Z() * q2.Z() + q1.W() * q2.W();
}

/// ��]�������C���ʂ�Quaternion�ƃx�N�g���̐ς�߂�
template<class ET, class BD>
inline TQuaternion<ET> mult(const TQuaternion<ET>& q, const PTM::TVectorBase<3, BD>& v){
	// ���ʂ̌v�Z�͉�]����Ƃ͈Ⴄ�̂ŁC�x�N�g����N�H�[�^�j�I���ɒ�������w������0�ɂ��Ȃ��Ɖ��Z�����������Ȃ�
	TQuaternion<ET> qv(0, ET(v[0]), ET(v[1]), ET (v[2]));
	return q*qv;
}

/// ��]�������C���ʂɃx�N�g����Quaternion�̐ς�߂�
template<class BD, class ET>
inline TQuaternion<ET> mult(const PTM::TVectorBase<3, BD>& v, const TQuaternion<ET>& q){
	TQuaternion<ET> qv(0, ET(v[0]), ET(v[1]), ET (v[2]));
	return qv*q;
}

template <class T1, class T2>
TQuaternion<T1> interpolate(T1 t, const TQuaternion<T1>& q1, const TQuaternion<T2>& q2){
	TQuaternion<T1> ret;
	TQuaternion<T1> q3 ;
    float      dot;

    dot = q1.X() * q2.X() + q1.Y() * q2.Y() + q1.Z() * q2.Z() + q1.W() * q2.W();
    
    // dot < 0.0f�̎��A���]����
    if (dot < 0.0f){
        dot = -dot;
        q3 = TQuaternion<T1>(-q2.W(), -q2.X(), -q2.Y(), -q2.Z());
    }
    else q3 = q2;
    
    if (dot >  1.0f) dot = 1.0f;
	if (dot < -1.0f) dot = -1.0f;
	
	float angle = acos(dot);
	float sina, sinat, sinaomt;
	
	sina    = sin(angle          );
	sinat   = sin(angle *      t );
	sinaomt = sin(angle * (1 - t));
	
	if (sina){
		ret.X() = (q1.X() * sinaomt + q3.X() * sinat) / sina;
		ret.Y() = (q1.Y() * sinaomt + q3.Y() * sinat) / sina;
		ret.Z() = (q1.Z() * sinaomt + q3.Z() * sinat) / sina;
		ret.W() = (q1.W() * sinaomt + q3.W() * sinat) / sina;
	}else{
		ret = q1;
	}
	return ret;
}

///	float��TQuaternion.
typedef TQuaternion<float> Quaternionf;
///	double��TQuaternion.
typedef TQuaternion<double> Quaterniond;


/**	�p���D�ʒu�ƌ�����\���N���X�D
	TQuaternion �� TVec3 �Ō����ƈʒu��\���D
	TAffine�̑���Ɏg����D
*/
template<class ET>
class TPose:public PTM::TVectorBase<7, TVecDesc<TPose<ET>, ET> >{
public:
	typedef TVecDesc<TPose<ET>, ET> desc;
	typedef PTM::TVectorBase<4, desc> base_type;
	///	�p������Ȃ���{�I�ȃ����o�̒�`.	@see ::DEF_TVECTOR_BASIC_MEMBER
	DEF_TVECTOR_BASIC_MEMBER(TPose);
	union{
		ET data[7];
		struct{
			ET w,x,y,z;		//< ��]
			ET px, py, pz;	//< �ʒu
		};
	};

	///	�v�f�̃A�N�Z�X
	ET& item_impl(size_t i){ return data[i]; }
	///	�v�f�̃A�N�Z�X
	const ET& item_impl(size_t i) const { return data[i]; }
	///	�X�g���C�h
	size_t stride_impl() const { return 1; }

	///	�v�f�̃A�N�Z�X
	TVec3<ET>& Pos() { return *(TVec3<ET>*)(data+4); }
	const TVec3<ET>& Pos() const { return *(TVec3<ET>*)(data+4); }
	TQuaternion<ET>& Ori() { return *(TQuaternion<ET>*)(void*)(data); }
	const TQuaternion<ET>& Ori() const { return *(TQuaternion<ET>*)(void*)(data); }
	ET& W(){return w;}
	const ET& W() const{return w;}
	ET& X(){return x;}
	const ET& X() const{return x;}
	ET& Y(){return y;}
	const ET& Y() const{return y;}
	ET& Z(){return z;}
	const ET& Z() const{return z;}
	ET& Px(){return px;}
	const ET& Px() const{return px;}
	ET& Py(){return py;}
	const ET& Py() const{return py;}
	ET& Pz(){return pz;}
	const ET& Pz() const{return pz;}

	/**@name	�v�f�ւ̃A�N�Z�X	*/
	//@{
	/// 
	ET& PosX() {return px;}
	const ET& PosX() const {return px;}
	/// 
	ET& PosY() {return py;}
	const ET& PosY() const {return py;}
	/// 
	ET& PosZ() {return pz;}
	const ET& PosZ() const {return pz;}
	/// 
	ET& OriX() {return x;}
	const ET& OriX() const {return x;}
	/// 
	ET& OriY() {return y;}
	const ET& OriY() const {return y;}
	/// 
	ET& OriZ() {return z;}
	const ET& OriZ() const {return z;}
	/// 
	ET& OriW() {return w;}
	const ET& OriW() const {return w;}
	
	TPose<ET> Inv() const { 
		TPose<ET> rv;
		rv.Ori() = Ori().Inv();
		rv.Pos() = -(rv.Ori()*Pos());
		return rv;
	}

	/**@name	�������ƍ\�z	*/
	TPose(const TVec3<ET>& p, const TQuaternion<ET>& q = TQuaternion<ET>()){
		Pos() = p;
		Ori() = q;
	}
	///	�P�ʍs��
	static TPose<ET> Unit(){
		TPose<ET> y;
		//PTM::init_unitize(y);
		y.Pos() = TVec3<ET>();
		y.Ori() = TQuaternion<ET>();
		return y;
	}

	///	���s�ړ�
	static TPose<ET> Trn(element_type px, element_type py, element_type pz){
		return Trn(TVec3<ET>(px, py, pz));
	}
	static TPose<ET> Trn(const TVec3<ET> &v){
		TPose<ET> y;
		y.Pos() = v;
		y.Ori() = TQuaternion<ET>();
		return y;
	}

	/// ��]
	static TPose<ET> Rot(ET wi, ET xi, ET yi, ET zi){ 
		TPose<ET> y;
		y.Pos() = TVec3<ET>();
		y.Ori() = TQuaternion<ET>(wi, xi, yi, zi);
		return y;
	}
	static TPose<ET> Rot(ET angle, const TVec3<element_type>& axis){ 
		TPose<ET> y;
		y.Pos() = TVec3<ET>();
		y.Ori() = TQuaternion<ET>::Rot(angle, axis);
		return y;
	}
	static TPose<ET> Rot(ET angle, char axis){
		TPose<ET> y;
		y.Pos() = TVec3<ET>();
		y.Ori() = TQuaternion<ET>::Rot(angle, axis);
		return y;
	}
	static TPose<ET> Rot(const TVec3<ET>& rot){
		TPose<ET> y;
		y.Pos() = TVec3<ET>();
		y.Ori() = TQuaternion<ET>::Rot(rot);
		return y;
	}
	static TPose<ET> Rot(const TQuaternion<ET> &q){
		TPose<ET> y;
		y.Pos() = TVec3<ET>();
		y.Ori() = q;
		return y;
	}

	/// Affine�ϊ��̍s�񂩂�ǂݏo���܂��D
	template <class AT>
	void FromAffine(const TAffine<AT>& f){
		/// Affine�s��̈ʒu�x�N�g����pose�̈ʒu��R�s�[����
		Pos() = f.Trn();
		/// Ori����ł���s���Affine�s��̑Ή�����ꏊ�ɏ㏑��
		Ori().FromMatrix(f.Rot());
	}

	/// Affine�ϊ��̍s��ɕϊ����Ԃ�
	template <class B>
	void ToAffine(TAffine<B>& af) const {
		/// Affine�s��̈ʒu�x�N�g����pose�̈ʒu��R�s�[����
		af.Trn() = Pos();
		/// Ori����ł���s���Affine�s��̑Ή�����ꏊ�ɏ㏑��
		Ori().ToMatrix(af.Rot());
	}

	operator TAffine<ET>(){ 
		TAffine<ET> rv;
		ToAffine(rv);
		return rv;
	}

	///@name �������E�\�z
	//@{
	///	�R���X�g���N�^
	template <class TW,class TX, class TY, class TZ,class TPX, class TPY, class TPZ> TPose (TW wi,TX xi, TY yi, TZ zi,TPX pxi, TPY pyi, TPZ pzi){
		W() = element_type(wi);
		X() = element_type(xi);
		Y() = element_type(yi);
		Z() = element_type(zi);
		Px() = element_type(pxi);
		Py() = element_type(pyi);
		Pz() = element_type(pzi);
	}
	template <class AT> TPose (const TAffine<AT>& af){
		FromAffine(af);
	}
	//@}

protected:
	///	�R���X�g���N�^
	void set_default(){ 
		W() = 1; X() = 0; Y() = 0; Z() = 0;
		Pos().clear();
	}
};
template <class EP, class EV>
TVec3<EV> operator * (const TPose<EP>& p, const TVec3<EV>& v){
	return p.Ori()*v + p.Pos();
}

template <class EA, class EB>
TPose<EA> operator * (const TPose<EA>& a, const TPose<EB>& b){
	TPose<EA> rv;
	rv.Pos() = a.Pos() + a.Ori() * b.Pos();
	rv.Ori() = a.Ori() * b.Ori();
	return rv;
}

///	float��TPose.
typedef TPose<float> Posef;
///	double��TPose.
typedef TPose<double> Posed;

//@}

//----------------------------------------------------------------------------
// SwingTwist
/** ��]�̃X�C���O�E�c�C�X�g�p�\�� */
struct SwingTwist : public Vec3d{
	double& SwingDir(){return item(0);}
	double& Swing(){return item(1);}
	double& Twist(){return item(2);}
	
	void ToQuaternion(Quaterniond& q){
		// tazz����̃�����(11)���A��[cos(psi), sin(psi), 0]^T�܂���theta������]������Z���܂���phi��]����quaternion
		double psi = SwingDir(), the = Swing(), phi = Twist();
		double cos_the = cos(the / 2), sin_the = sin(the / 2);
		double cos_phi = cos(phi / 2), sin_phi = sin(phi / 2);
		double cos_psiphi = cos(psi - phi / 2), sin_psiphi = sin(psi - phi / 2);
		q.w = cos_the * cos_phi;
		q.x = sin_the * cos_psiphi;
		q.y = sin_the * sin_psiphi;
		q.z = cos_the * sin_phi;
	}
	
	void FromQuaternion(const Quaterniond& q){
		// tazz����̃�����(12)���Aitem[0]:psi, item[1]:theta, item[2]:phi
		item(0) = atan2(q.w * q.y + q.x * q.z, q.w * q.x - q.y * q.z);
		item(1) = 2 * atan2(sqrt(q.x * q.x + q.y * q.y), sqrt(q.w * q.w + q.z * q.z));
		item(2) = 2 * atan2(q.z, q.w);
	}
	
	void Jacobian(Matrix3d& J){
		// tazz����̃�����(13)���Ast=[psi, theta, phi]^T�̎��Ԕ�������p���x�ւ�^���郄�R�r�A��J (�� = J * (d/dt)st)
		double psi = SwingDir();
		double the = std::max(Rad(1.0), Swing());	// �X�C���O�p0�Ń����N��������̂Ŗ��������
		double cos_psi = cos(psi), sin_psi = sin(psi);
		double cos_the = cos(the), sin_the = sin(the);
		J[0][0] = -sin_the * sin_psi;
		J[0][1] =  cos_psi;
		J[0][2] =  sin_the * sin_psi;
		J[1][0] =  sin_the * cos_psi;
		J[1][1] =  sin_psi;
		J[1][2] = -sin_the * cos_psi;
		J[2][0] =  1.0 - cos_the;
		J[2][1] =  0.0;
		J[2][2] =  cos_the;
	}
	
	void JacobianInverse(Matrix3d& J, const Quaterniond& q){
		// tazz����̃�����(14)���A�p���x�ւ���st=[psi, theta, phi]^T�̎��Ԕ�����߂郄�R�r�A��JInv ((d/dt)st = JInv * ��)
		const double eps = 1.0e-2;									// (14)���̕��ꂪ0�ɂȂ邱�Ƃ�h�����߂�eps�B���������߂���Ɓi1.0e-12�Ƃ�����Ɓj0�t�߂ŉ��ɂ����Ƃ��ɕ��̂��O��Ă��܂�
		double w2z2 = std::max(eps, q.w * q.w + q.z * q.z);
		double w2z2inv = 1.0 / w2z2;
		double x2y2 = std::max(eps, 1.0 - w2z2);
		double x2y2inv = 1.0 / x2y2;
		double tmp = sqrt(w2z2inv * x2y2inv);
		double wy_xz = q.w * q.y + q.x * q.z;
		double wx_yz = q.w * q.x - q.y * q.z;
		J[0][0] =  0.5 * (w2z2inv - x2y2inv) * wy_xz;
		J[0][1] = -0.5 * (w2z2inv - x2y2inv) * wx_yz;
		J[0][2] =  1.0;
		J[1][0] =  tmp * wx_yz;
		J[1][1] =  tmp * wy_xz;
		J[1][2] =  0.0;
		J[2][0] =  w2z2inv * wy_xz;
		J[2][1] = -w2z2inv * wx_yz;
		J[2][2] =  1.0;
	}
	
	void Coriolis(Vec3d& c, const Vec3d& sd){
		double cos_psi = cos(SwingDir()), sin_psi = sin(SwingDir());
		double cos_the = cos(Swing()), sin_the = sin(Swing());
		double tmp1 = sd[1] * (sd[0] - sd[2]);
		double tmp2 = sd[0] * (sd[0] - sd[2]);
		double tmp3 = sd[0] * sd[1];
		c[0] = -cos_the * sin_psi * tmp1 - sin_the * cos_psi * tmp2 - sin_psi * tmp3;
		c[1] =  cos_the * cos_psi * tmp1 - sin_the * sin_psi * tmp2 + cos_psi * tmp3;
		c[2] =  sin_the * tmp1;	
	}
};

}
#endif
