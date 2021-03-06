/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_VISUALIZE_DRAWUTIL_H
#define HK_VISUALIZE_DRAWUTIL_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Types/Color/hkColor.h>

class hkLocalFrame;
struct hkGeometry;

/// This class facilitates drawing cones, arrows, planes representing ragdoll limits.
class HK_EXPORT_COMMON hkDrawUtil: public hkReferencedObject
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TOOLS);

		hkDrawUtil(hkReal new_scale);

			/// Displays an oriented point.
		void displayOrientedPoint(const hkVector4& position,const hkRotation& rot,hkReal size,hkColor::Argb color);

			/// Displays a point.
		void displayPoint(const hkVector4& position,hkReal size,hkColor::Argb color);

			/// Displays a line segment.
		void displaySegment(const hkVector4& p1, const hkVector4& p2, hkColor::Argb color);

			/// Displays a cone.
		void displayCone (hkReal cone_angle, const hkVector4& startPos, const hkVector4& coneAaxis, const hkVector4& perpVector, int numSegments, hkColor::Argb color);

			/// Displays a plane.
		void displayPlane (const hkVector4& startPos, const hkVector4& planeNormal, const hkVector4& vectorOnPlane, hkColor::Argb color, hkBool showNormal = true);

			/// Displays an arrow.
		void displayArrow (const hkVector4& startPos, const hkVector4& arrowDirection, const hkVector4& perpDirection, hkColor::Argb color);

			/// Displays a rectangle on the plane containing the binormal and tangent of a normal
		void displayOrientedRectangle (const hkVector4& center, const hkVector4& binormal, const hkVector4& tangent, hkReal length, hkReal width, hkColor::Argb color);
        
			/// Draws a semi circle.
			/// \param center The position of the center in world space
			/// \param normal The axis about which the circle is drawn
			/// \param startPerp An orthogonal axis to the normal which defines the start of the sweep
		void drawSemiCircle(const hkVector4& center, hkVector4& normal, 
						    hkVector4& startPerp, hkReal thetaMin, hkReal thetaMax,
							hkReal radius,int numSegments, 
							hkColor::Argb color);

			/// Gets the scale by which the visual representation of cones, arrows and planes will be scaled.
		hkReal getScale();

			/// Sets the scale by which the visual representation of cones, arrows and planes will be scaled.
		void setScale(hkReal new_scale);
	
			/// Display two planes at the given heights above the base location.
			/// The normal dictates the plane the rectangles will be parallel to, with the given length and width.
			/// A line is drawn connecting the rectangle centroids, and a label is drawn if given.
		void displayMinMaxRectangleWidget( const hkTransform& locationOfBase, const hkVector4& normal, hkReal length, hkReal width, hkReal minHeight, hkReal maxHeight, const hkStringPtr& label, hkColor::Argb color, int tag);

			/// Displays a graphical representation of the given hinge axis and angle range.
			/// The parent vector defines 0 radians rotation, and along with the normal defines the plane of the semicircle.
			/// The child vector is used to ensure the semicircle is displayed on the inside of the hinge
		void displayAxisAngleWidget( const hkVector4& location, const hkVector4& normal, const hkVector4& parent, const hkVector4& child, hkReal minRadians, hkReal maxRadians, hkReal radius, hkInt32 numSegments, hkColor::Argb color, int tag);

			/// Display local frame. If drawChildren is true all children of the local frame will be drawn. Use
			/// annotation to add an additional string after the local frame name.
		static void HK_CALL displayLocalFrame( const hkLocalFrame& localFrame, const hkTransform& worldFromModel, hkReal size, bool drawChildren = true, hkColor::Argb color = hkColor::WHITE, const char* annotation = HK_NULL);

		/// Input for debugDisplayGeometry
		struct HK_EXPORT_COMMON DebugDisplayGeometrySettings
		{
			DebugDisplayGeometrySettings()
			{
				m_vertexColor = hkColor::WHITE;
				m_edgeColor = hkColor::BLACK;
				m_triangleColor = hkColor::RED;
				m_triangleLabelColor = hkColor::BLACK;

				m_showVertices = true;
				m_onlyShowTriangleVertices = true;
				m_showEdges = true;
				m_showTriangles = true;

				m_labelTriangles = false;
				m_labelVertices = false;

				m_showTriangleNormals = false;

				m_forceColorTrianglesByMaterial = false;
				m_lightTriangles = false;
				m_lightDirection.set(0.0f, 0.0f, 1.0f );

				m_skipTriangles = 1;

				m_cullingAabb.setEmpty();
			}

			hkColor::Argb m_triangleColor;
			hkColor::Argb m_edgeColor;
			hkColor::Argb m_vertexColor;
			hkColor::Argb m_triangleLabelColor;

				/// Whether or not to display crosses for the geometry vertices.
			hkBool m_showVertices;
				/// If true, only vertices that belong to a triangle will be shown.
			hkBool m_onlyShowTriangleVertices;
			hkBool m_showEdges;
			hkBool m_showTriangles;

			hkBool m_labelTriangles;
			hkBool m_labelVertices;

			hkBool m_showTriangleNormals;

			// Ignore m_triangleColor and use material index to access hkColor::s_colorTable
			hkBool m_forceColorTrianglesByMaterial;
			hkBool m_lightTriangles;
			hkVector4 m_lightDirection;

			// For very large geometries, rendering may be slow. Set skipTriangles to n > 1 to render every nth triangle
			int m_skipTriangles;
			// Cull triangles displayed to only those whose aabb overlaps this aabb
			hkAabb m_cullingAabb;
		};

		/// Displays a hkGeometry as HK_DISPLAY_LINEs and HK_DISPLAY_TRIANGLEs
		static void HK_CALL debugDisplayGeometry(const hkGeometry& triMesh, const DebugDisplayGeometrySettings& settings);

	protected:
		hkReal m_scale;
};

#endif // HK_VISUALIZE_DRAWUTIL_H

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20140907)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
