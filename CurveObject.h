#pragma once
#include "Object.h"
#include "Line.h"

#define MIN 0.0f

class CurveObject : public Object
{
	private:
		Line m_line;
		float m_step = 10.0f;
		float m_current = 0.0f;
		float m_range = 1000.0f;
		

		float nextStep();
	public:
		CurveObject(Line line);
		void operation()override;	
		inline bool isComposite()override { return true; }
};

