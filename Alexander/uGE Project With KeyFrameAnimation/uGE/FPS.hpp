#ifndef FPS_H
#define FPS_H


class FPS
{
	private:
		FPS(){}

	public:
		static void update();
		static unsigned int getFPS();

	private:
		static float startTime;
		static unsigned int count;
		static unsigned int fps;
};

#endif // FPS_H
