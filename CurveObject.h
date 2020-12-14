#pragma once
#include "Object.h"
#include "Curve.h"

#define MIN 0.0f

//object that follows a curve
class CurveObject : public Object
{
	private:
		//the curve
		Curve *m_curve;

		//step
		float m_step = 0.01f;

		//current parameter (0.0-m_range)
		float m_current = 0.0f;

		//range of the parameter
		float m_range = 0.5f;
		
		//calculates next step
		float nextStep();

	public:
		CurveObject(Curve *curve);
		void operation()override;	
		inline bool isComposite()override { return true; }
};

