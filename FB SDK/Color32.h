#ifndef _COLOR32_H
#define _COLOR32_H

//#include "../Frostbite_classes.h"

namespace fb
{

	class Color32
	{
	public:
		union
		{
			struct
			{
				BYTE R;
				BYTE G;
				BYTE B;
				BYTE A;
			};
			DWORD dwColor;
		};

	public:
		Color32(const DWORD _Color)
		{
			dwColor=_Color;
		}

		Color32(const BYTE Red,const BYTE Green,const BYTE Blue, const BYTE Alpha)
		{
			A=Alpha;
			R=Red;
			G=Green;
			B=Blue;
		}
	};


};

#endif