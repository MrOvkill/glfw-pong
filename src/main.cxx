/*
	GLFW Pong
	Copyright (c) 2014 Samuel "MrOverkill" Meyers
	Public Domain
*/

#include <GLFW/glfw3.h>
#include "util.hpp"
#include "ball.hpp"
#include <cstdio>
#include <cstdlib>

// Are we going up?  Are we going down?
bool p1u, p1d;

// Where it's at, yo
float p1y;

/*
	0100001101010000010101010010000001011001
	010000110101000001010101001000000101001101010000010001010100010101000100
	http://www.roubaixinteractive.com/PlayGround/Binary_Conversion/Binary_To_Text.asp
*/
float cpy, cpi;

// Oh noes!
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}


// Teh keys!
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
    	p1u = true;
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
    	p1u = false;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
    	p1d = true;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
    	p1d = false;
    }
}

int main(void)
{
		// Create a new util
		ovk::util::Util util = ovk::util::Util();
		
		// Create a new ball
		ovk::pong::Ball ball = ovk::pong::Ball(util);
		
		// Set both players to 0 on their Y axes
		p1y = 0;
		cpy = 0;
		
		// Set the CPU player's initial intelligence
		cpi = util.randFloat(0.001f, 0.01f);
		
		// Dat window
    GLFWwindow* window;
    
    // Setup error handling
    glfwSetErrorCallback(error_callback);
    
    // Oh noes!  GLFW couldn't init!
    if (!glfwInit())
    		// Say goodnight, Gracie!
        exit(EXIT_FAILURE);
        
    // Make an 800x600 OpenGL window called "Pong"
    window = glfwCreateWindow(800, 600, "Pong", NULL, NULL);
    
    // Oh noes!  We couldn't make a window! :(
    if (!window)
    {
    		// Say goodnight, Gracie!
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Make the window what OpenGL draws to
    glfwMakeContextCurrent(window);
    
    // Setup the keyboard functions
    glfwSetKeyCallback(window, key_callback);
    
    // Decide the initial direction and velocity
    ball.start();
    
    // As long as someone hasn't shut the window, do stuff
    while (!glfwWindowShouldClose(window))
    {
    		// Do movement on the ball's X and Y axes
    		ball.tick();
    		
    		// If the ball went past the computer, player wins
    		if(ball.x >= 1.4f)
    		{
    			printf("Player wins!\n");
    			return 0;
    		}
    		
    		// If the ball went past the player, computer wins
    		if (ball.x <= -1.4f)
    		{
    			printf("Computer wins!\n");
    			return 0;
    		}
    		
    		// If the ball is too low, bounce up
    		if (ball.y >= 1.0f)
    		{
    			ball.collideUp();
    		}
    		
    		// If the ball is too high, bounce down
    		if (ball.y <= -1.0f)
    		{
    			ball.collideDown();
    		}
    		
    		/*
    			If the up key is pressed,
    			and if the player is within the limit
    			on the y axis, go up
    		*/
    		if (p1u && p1y <= 1)
    		{
    			p1y += 0.01f;
    		}
    		
    		/*
    			If the down key is pressed,
    			and if the player is within the limit
    			on the y axis, go down
    		*/
    		if (p1d && p1y >= -1)
    		{
    			p1y -= 0.01f;
    		}
    		
    		// Do up if the ball is higher
    		if (ball.y > cpy)
    		{
    			cpy += cpi;
    		}
    		
    		// Go down if the ball is lower
    		if (ball.y < cpy)
    		{
    			cpy -= cpi;
    		}
    		
    		// Check collisions for Player's paddle
    		if((ball.x <= -1.15f) && (ball.x >= -1.25f) && (ball.y <= p1y+0.15) && (ball.y >= p1y-0.15))
    		{
    			ball.collideRight();
    			cpi += util.randFloat(0.001f, 0.005f);
    		}
    		
    		// Check collisions for AI's paddle
    		if((ball.x >= 1.15f) && (ball.x <= 1.25f) && (ball.y <= cpy+0.15) && (ball.y >= cpy-0.15))
    		{
    			ball.collideLeft();
    			cpi += util.randFloat(0.001f, 0.005f);
    		}
    		
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Draw player paddle
        glPushMatrix();
        glTranslatef(-1.2f, p1y, 0);
        glScalef(0.05f, 0.05f, 1);
        glBegin(GL_QUADS);
        glColor3f(0.f, 0.0f, 0.5f);
        glVertex3f(-0.5f, -2.0f, 0.0f);
        glVertex3f(-0.5f, 2.0f, 0.0f);
        glVertex3f(0.5f, 2.0f, 0.0f);
        glVertex3f(0.5f, -2.0f, 0.0f);
        glEnd();
        glPopMatrix();
        
        // Draw ball
        glPushMatrix();
        glTranslatef(ball.x, ball.y, 0);
        glScalef(0.05f, 0.05f, 1);
        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f(-0.5f, 0.5f, 0.0f);
        glVertex3f(0.5f, 0.5f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.0f);
        glEnd();
        glPopMatrix();
        
        // Draw AI paddle
        glPushMatrix();
        glTranslatef(1.2f, cpy, 0);
        glScalef(0.05f, 0.05f, 1);
        glBegin(GL_QUADS);
        glColor3f(0.f, 0.5f, 0.0f);
        glVertex3f(-0.5f, -2.0f, 0.0f);
        glVertex3f(-0.5f, 2.0f, 0.0f);
        glVertex3f(0.5f, 2.0f, 0.0f);
        glVertex3f(0.5f, -2.0f, 0.0f);
        glEnd();
        glPopMatrix();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
