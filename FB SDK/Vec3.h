#ifndef _VEC3_H
#define _VEC3_H

//#include "../Frostbite_classes.h"

namespace fb
{

	class Vec3
	{
	public:
		union
		{
			struct 
			{
				FLOAT x;
				FLOAT y;
				FLOAT z;
				FLOAT w;
			};
			FLOAT data[4];
		};

		float len(void)
		{
			return sqrt(x*x+y*y+z*z);
		}
		void normalize(void)
		{
			float _l=len();
			this->x/=_l;
			this->y/=_l;
			this->z/=_l;
		}
		Vec3 operator * (float const &other)
		{
			this->x*=other;
			this->y*=other;
			this->z*=other;
			return *this;
		}
		Vec3 operator + (Vec3 const &other)
		{
			Vec3 v;
			v.x=this->x+other.x;
			v.y=this->y+other.y;
			v.z=this->z+other.z;
			return v;
		}
		Vec3 operator - (Vec3 const &other)
		{
			Vec3 v;
			v.x=this->x-other.x;
			v.y=this->y-other.y;
			v.z=this->z-other.z;
			return v;
		}
		Vec3 operator += (Vec3 const &other)
		{
			this->x+=other.x;
			this->y+=other.y;
			this->z+=other.z;
			return *this;
		}
		//new from me 
		Vec3 operator -= (Vec3 const &other)
		{
			this->x-=other.x;
			this->y-=other.y;
			this->z-=other.z;
			return *this;
		}
		//new from me Calculate Dotproduct
		float Dot( Vec3 Vec )
        {
            return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z;
        }

		// new from me get VecLength
		float VectorLength()
		{
			return sqrt( ((this->x)*(this->x)) + ((this->y)*(this->y)) + ((this->z)*(this->z)));
		}

		//new from me get distance to vec
		float DistanceToVector( Vec3 const &other )
        {
			Vec3 Distance;
			Distance.x = other.x - this->x;
			Distance.y = other.y - this->y;
			Distance.z = other.z - this->z;
            return sqrt( ( Distance.x * Distance.x ) + ( Distance.y * Distance.y ) + ( Distance.z * Distance.z ) );
        }

		//new from me calc Veccrossize
		Vec3 VectorCrossSize (CONST Vec3 *pV1, CONST Vec3 *pV2 )
		{
			 this->x = pV1->y * pV2->z - pV1->z * pV2->y;
			 this->y = pV1->z * pV2->x - pV1->x * pV2->z;
			 this->z = pV1->x * pV2->y - pV1->y * pV2->x;
			return *this;
		}

		BOOL WorldToScreen( __out Vec3 *screen )
		{
			static DWORD Function = NULL;

			// Make sure the 
			if (screen == NULL)
				return FALSE;

			// Get the WorldToScreen Function
			if (Function == NULL)
				Function = WORLDTOSCREEN;
			

			__asm
			{
				MOV	ECX, screen;
				PUSH	ECX;
				MOV	ECX, this;
				CALL	Function;
			}
		}




	};



};

#endif