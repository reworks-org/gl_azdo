///
/// DebugRenderer.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_DEBUGRENDERER_HPP_
#define GALAXY_GRAPHICS_DEBUGRENDERER_HPP_

#include <glm/mat4x4.hpp>

#include "galaxy/graphics/gl/Shader.hpp"
#include "galaxy/graphics/gl/Texture.hpp"
#include "galaxy/graphics/gl/VertexArray.hpp"

namespace galaxy
{
	class debug_render final
	{
	public:
		static void clear();
		static void begin();
		static void set_state();

		static void set_viewport(const int width, const int height);

		static void draw(Shader& shader, VertexArray& vao);

	private:
		inline static int       m_width  = 0;
		inline static int       m_height = 0;
		inline static glm::mat4 m_proj   = glm::mat4 {1.0f};
	};
} // namespace galaxy

#endif
