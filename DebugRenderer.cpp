///
/// debug_render.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "DebugRenderer.hpp"

// must be between -1.0f and 1.0f for orthographic.
// https://stackoverflow.com/q/78664551
static float max_depth = 1.0f;
static float min_depth = -1.0f;

namespace galaxy
{
	void debug_render::clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(max_depth); // clears anything below that.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void debug_render::begin()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_width, m_height);
	}

	void debug_render::set_state()
	{
		glDisable(GL_FRAMEBUFFER_SRGB);
		glDisable(GL_CULL_FACE);
		glDisable(GL_SCISSOR_TEST);
		glDisable(GL_MULTISAMPLE);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);

		glCullFace(GL_BACK);
		glDepthFunc(GL_LEQUAL);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);
	}

	void debug_render::set_viewport(const int width, const int height)
	{
		m_width  = width;
		m_height = height;
		m_proj   = glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, min_depth, max_depth);
	}

	void debug_render::draw(Shader& shader, VertexArray& vao)
	{
		vao.bind();

		shader.set_uniform("u_projection", m_proj);
		shader.set_uniform("u_transform", glm::mat4x4 {1.0f});

		glDrawElements(GL_TRIANGLES, vao.count(), GL_UNSIGNED_INT, vao.offset());
	}
} // namespace galaxy
