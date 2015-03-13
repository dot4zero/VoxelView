// VoxelView.cpp : Defines the exported functions for the DLL application.
//

#include "Common\voxres.hpp"
#include "RefString.h"

namespace VoxelView
{

public ref class VoxelViewController
{
private:
	TVoxelBox* m_voxelBox;
	TVoxelRes* m_voxelRes;
	bool m_cancel;
	bool m_percent;
	bool m_isolines;
	unsigned int m_depth;
	unsigned int m_axis;
	unsigned int m_levels;
	unsigned int m_progress;
	unsigned int m_refCount;
	System::Drawing::Pen^ m_dotPen;
	System::Drawing::Size m_size;
	System::Drawing::SizeF m_boxSize;
	System::Drawing::Rectangle m_bounds;
	System::Drawing::Point m_crossCenter;

public:
	VoxelViewController()
	{
		m_voxelBox = NULL;
		m_voxelRes = NULL;
		m_axis = 0;
		m_depth = 0;
		m_levels = 10;
		m_progress = 0;
		m_refCount = 1;
		m_cancel = false;
		m_percent = true;
		m_isolines = false;
		m_size = System::Drawing::Size::Empty;
		m_boxSize = System::Drawing::SizeF::Empty;
		m_bounds = System::Drawing::Rectangle::Empty;
		m_crossCenter = System::Drawing::Point::Empty;
		m_dotPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
		m_dotPen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
	}

	~VoxelViewController()
	{
	}

	void IncRefCount()
	{
		m_refCount++;
	}

	void DecRefCount()
	{
		if (--m_refCount < 1)
		{
			if (m_voxelBox != NULL)
			{
				delete m_voxelBox;
				m_voxelBox = NULL;
			}

			if (m_voxelRes != NULL)
			{
				delete m_voxelRes;
				m_voxelRes = NULL;
			}
		}
	}

	property int RefCount {
		int get() { return m_refCount; }}

	property bool HasResult {
		bool get() { return m_voxelRes != NULL; }}

	property int ResultID {
		int get() { return m_voxelRes->getResultID(); }}

	property int ParticleID {
		int get() { return m_voxelRes->getParticleID(); }}

	property double Hist {
		double get() { return m_voxelRes->getHist(); }}

	property unsigned int SizeX {
		unsigned int get() { return m_voxelBox->getSizeX(); }}

	property unsigned int SizeY {
		unsigned int get() { return m_voxelBox->getSizeY(); }}

	property unsigned int SizeZ {
		unsigned int get() { return m_voxelBox->getSizeZ(); }}

	property float BoxSizeX {
		float get() { return m_voxelBox->getBoxSizeX(); }}

	property float BoxSizeY {
		float get() { return m_voxelBox->getBoxSizeY(); }}

	property float BoxSizeZ {
		float get() { return m_voxelBox->getBoxSizeZ(); }}

	property bool Percent {
		bool get() { return m_percent; }
		void set(bool value) { m_percent = value; }}

	property bool Isolines {
		bool get() { return m_isolines; }
		void set(bool value) { m_isolines = value; }}

	property unsigned int Axis {
		unsigned int get() { return m_axis; }
		void set(unsigned int value)
		{
			m_axis = value;

			if (m_axis == 0)
			{
				m_size.Width = m_voxelBox->getSizeY();
				m_size.Height = m_voxelBox->getSizeZ();
				m_boxSize.Width = m_voxelBox->getBoxSizeY();
				m_boxSize.Height = m_voxelBox->getBoxSizeZ();
			}
			else if (m_axis == 1)
			{
				m_size.Width = m_voxelBox->getSizeX();
				m_size.Height = m_voxelBox->getSizeZ();
				m_boxSize.Width = m_voxelBox->getBoxSizeX();
				m_boxSize.Height = m_voxelBox->getBoxSizeZ();
			}
			else if (m_axis == 2)
			{
				m_size.Width = m_voxelBox->getSizeX();
				m_size.Height = m_voxelBox->getSizeY();
				m_boxSize.Width = m_voxelBox->getBoxSizeX();
				m_boxSize.Height = m_voxelBox->getBoxSizeY();
			}

			m_depth = 0;
			m_bounds = System::Drawing::Rectangle(0, 0, m_size.Width, m_size.Height);

			if (m_crossCenter.X >= m_size.Width)
				m_crossCenter.X = m_size.Width - 1;

			if (m_crossCenter.Y >= m_size.Height)
				m_crossCenter.Y = m_size.Height - 1;
		}}

	property bool Cancel {
		void set(bool value) { m_cancel = value; }}

	property unsigned int Progress {
		unsigned int get() { return m_progress; }}

	property unsigned int Depth {
		unsigned int get() { return m_depth; }
		void set(unsigned int value) { m_depth = value; }}

	property unsigned int Levels {
		unsigned int get() { return m_levels; }
		void set(unsigned int value) { m_levels = value; }}

	property System::Drawing::Rectangle Bounds {
		System::Drawing::Rectangle get() { return m_bounds; }
		void set(System::Drawing::Rectangle value) { m_bounds = value; }}

	property System::Drawing::Size Size {
		System::Drawing::Size get() { return m_size; }
		void set(System::Drawing::Size value) { m_size = value; }}

	property System::Drawing::SizeF BoxSize {
		System::Drawing::SizeF get() { return m_boxSize; }
		void set(System::Drawing::SizeF value) { m_boxSize = value; }}

	property System::Drawing::Point CrossCenter {
		System::Drawing::Point get() { return m_crossCenter; }
		void set(System::Drawing::Point value)
		{
			m_crossCenter = value;

			if (m_crossCenter.X < 0)
				m_crossCenter.X = 0;

			if (m_crossCenter.X >= m_size.Width)
				m_crossCenter.X = m_size.Width - 1;

			if (m_crossCenter.Y < 0)
				m_crossCenter.Y = 0;

			if (m_crossCenter.Y >= m_size.Height)
				m_crossCenter.Y = m_size.Height - 1;
		}}

	static System::Collections::Generic::Dictionary<int, int>^ GetColorMap()
	{
		System::Collections::Generic::Dictionary<int, int>^ map = 
			gcnew System::Collections::Generic::Dictionary<int, int>();

		std::map<int, int> colorMap = TVoxelBox::getColorMap();
		std::map <int, int>::iterator iter;
		for (iter = colorMap.begin(); iter != colorMap.end(); iter++)
			map[iter->first] = iter->second;

		return map;
	}

	static void SetColorValue(int material, int color)
	{
		TVoxelBox::setColorValue(material, color);
	}

	static int GetColorValue(int material)
	{
		return TVoxelBox::getColorValue(material);
	}

	cli::array<int>^ GetMaterials()
	{
		std::vector<int> materials = m_voxelBox->getMaterials();
		cli::array<int>^ list = gcnew cli::array<int>(materials.size());
		for (int i = 0; i < materials.size(); i++)
			list[i] = materials[i];
		return list;
	}

	int GetMaterial(System::Drawing::Point p)
	{
		if (m_voxelBox != NULL)
		{
			if (m_axis == 0)
			{
				return m_voxelBox->getMaterial(m_depth, p.X, p.Y);
			}
			else if (m_axis == 1)
			{
				return m_voxelBox->getMaterial(p.X, m_depth, p.Y);
			}
			else if (m_axis == 2)
			{
				return m_voxelBox->getMaterial(p.X, p.Y, m_depth);
			}
		}

		return 0;
	}

	float GetValue(int i)
	{
		if (m_voxelRes != NULL)
		{
			if (m_axis == 0)
			{
				return m_voxelRes->getValue(i, m_crossCenter.X, m_crossCenter.Y);
			}
			else if (m_axis == 1)
			{
				return m_voxelRes->getValue(m_crossCenter.X, i, m_crossCenter.Y);
			}
			else if (m_axis == 2)
			{
				return m_voxelRes->getValue(m_crossCenter.X, m_crossCenter.Y, i);
			}
		}

		return 0;
	}

	float GetValue(System::Drawing::Point p)
	{
		if (m_voxelRes != NULL)
		{
			if (m_axis == 0)
			{
				return m_voxelRes->getValue(m_depth, p.X, p.Y);
			}
			else if (m_axis == 1)
			{
				return m_voxelRes->getValue(p.X, m_depth, p.Y);
			}
			else if (m_axis == 2)
			{
				return m_voxelRes->getValue(p.X, p.Y, m_depth);
			}
		}

		return 0;
	}

	float GetNormValue(System::Drawing::Point p)
	{
		if (m_voxelRes != NULL)
		{
			if (m_axis == 0)
			{
				return m_voxelRes->getNormValue(m_depth, p.X, p.Y);
			}
			else if (m_axis == 1)
			{
				return m_voxelRes->getNormValue(p.X, m_depth, p.Y);
			}
			else if (m_axis == 2)
			{
				return m_voxelRes->getNormValue(p.X, p.Y, m_depth);
			}
		}

		return 0;
	}

	void InitVoxelBox(RefString fileName)
	{
		TVoxelBox* voxelBox = new TVoxelBox();

		try
		{
			voxelBox->Init(fileName.c_str());
		}
		catch (Exception e)
		{
			delete m_voxelBox;
			m_voxelBox = NULL;
			throw gcnew System::Exception(RefString(e.m_err));
		}

		if (m_voxelBox != NULL)
			delete m_voxelBox;

		m_voxelBox = voxelBox;

		if (m_voxelBox->getSizeY() > 1 && m_voxelBox->getSizeZ() > 1)
			Axis = 0;
		else if (m_voxelBox->getSizeX() > 1 && m_voxelBox->getSizeZ() > 1)
			Axis = 1;
		else if (m_voxelBox->getSizeX() > 1 && m_voxelBox->getSizeY() > 1)
			Axis = 2;
		else
			throw gcnew System::Exception("Не правильно заданы размеры воксельбокса!");
	}

	void InitVoxelRes(RefString fileName)
	{
		TVoxelRes* voxelRes = new TVoxelRes(m_voxelBox);

		try
		{
			voxelRes->Init(fileName.c_str());
		}
		catch (Exception e)
		{
			delete voxelRes;
			throw gcnew System::Exception(RefString(e.m_err));
		}

		if (m_voxelRes != NULL)
			delete m_voxelRes;

		m_voxelRes = voxelRes;
	}

	System::Drawing::Bitmap^ CreateImageVoxelBox()
	{
		System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(m_size.Width, m_size.Height);
		System::Drawing::Graphics^ graphics = System::Drawing::Graphics::FromImage(bitmap);
		HDC hdc = (HDC)(void*)graphics->GetHdc();

		m_progress = 0;
		m_cancel = false;

		m_voxelBox->clearMaterials();

		for (int i = 0; i < m_size.Width; i++)
		{
			for (int j = 0; j < m_size.Height; j++)
			{
				int color = -1;
				int material = 0;

				if (m_axis == 0)
				{
					material = m_voxelBox->getMaterial(m_depth, i, j);
				}
				else if (m_axis == 1)
				{
					material = m_voxelBox->getMaterial(i, m_depth, j);
				}
				else if (m_axis == 2)
				{
					material = m_voxelBox->getMaterial(i, j, m_depth);
				}

				if (material > 0)
				{
					m_voxelBox->putMaterial(material);
					int color = GetColorValue(material);
					SetPixel(hdc, i, j, RGB(color, color, color));
				}

				if (m_cancel)
				{
					m_cancel = false;
					return nullptr;
				}
			}

			m_progress = ((float)i/(float)m_size.Width)*100;
		}

		graphics->ReleaseHdc();
		return bitmap;
	}

	System::Drawing::Bitmap^ CreateImageVoxelRes()
	{
		System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(m_size.Width, m_size.Height);
		System::Drawing::Graphics^ graphics = System::Drawing::Graphics::FromImage(bitmap);
		HDC hdc = (HDC)(void*)graphics->GetHdc();

		m_progress = 0;
		m_cancel = false;

		for (int i = 0; i < m_size.Width; i++)
		{
			for (int j = 0; j < m_size.Height; j++)
			{
				int color = -1;

				if (m_axis == 0)
				{
					color = m_voxelRes->getColorValue(m_depth, i, j, m_isolines, m_levels);
				}
				else if (m_axis == 1)
				{
					color = m_voxelRes->getColorValue(i, m_depth, j, m_isolines, m_levels);
				}
				else if (m_axis == 2)
				{
					color = m_voxelRes->getColorValue(i, j, m_depth, m_isolines, m_levels);
				}

				if (color >= 0)
					SetPixel(hdc, i, j, color);

				if (m_cancel)
				{
					m_cancel = false;
					return nullptr;
				}
			}

			m_progress = ((float)i/(float)m_size.Width)*100;
		}

		graphics->ReleaseHdc();
		return bitmap;
	}

	void DrawGrid(System::Drawing::Graphics^ graphics, System::Drawing::Font^ font, System::Drawing::Rectangle bounds)
	{
		int step = m_bounds.Width;
		int left = m_bounds.Left;
		int right = m_bounds.Right;
		CalcGridParams(left, right, step);
		if (left < m_bounds.Left) left+=step;

		for (int i = left; i <= right; i+=step)
		{
			int k = (int)((bounds.Width-60.0f)*(((float)(i-m_bounds.Left))/((float)m_bounds.Width)));
			graphics->DrawLine(System::Drawing::Pens::Black, bounds.Left+k+40, bounds.Bottom-20, bounds.Left+k+40, bounds.Bottom-17);

			float j = m_boxSize.Width*((float)i)*10;
			System::String^ s = System::String::Format("{0:f2}", j);
			System::Drawing::SizeF strSize = graphics->MeasureString(s, font);
			graphics->DrawString(s, font, System::Drawing::Brushes::Black, bounds.Left+k-strSize.Width/2+40.0f, bounds.Bottom-15.0f);
		}

		//for (int i = left; i <= right; i++)
		//{
		//	int k = (int)((size.Width-60.0f)*(((float)(i-m_bounds.Left))/((float)m_bounds.Width)));
		//	graphics->DrawLine(m_dotPen, k+40, 20, k+40, size.Height-20);
		//}

		step = m_bounds.Height;
		int top = m_bounds.Top;
		int bottom = m_bounds.Bottom;
		CalcGridParams(top, bottom, step);
		if (top < m_bounds.Top) top+=step;

		for (int i = top; i <= bottom; i+=step)
		{
			int k = (int)((bounds.Height-40.0f)*(((float)(i-m_bounds.Top))/((float)m_bounds.Height)));
			graphics->DrawLine(System::Drawing::Pens::Black, bounds.Left+37, bounds.Top+k+20, bounds.Left+40, bounds.Top+k+20);

			float j = m_boxSize.Height*((float)i)*10;
			System::String^ s = System::String::Format("{0:f2}", j);
			System::Drawing::SizeF strSize = graphics->MeasureString(s, font);
			graphics->DrawString(s, font, System::Drawing::Brushes::Black, bounds.Left+37.0f-strSize.Width, bounds.Top+k-strSize.Height/2+20.0f);
		}

		graphics->DrawRectangle(System::Drawing::Pens::Black, bounds.Left+40, bounds.Top+20, bounds.Width-60, bounds.Height-40);
	}

	void DrawColorBar(System::Drawing::Graphics^ graphics, System::Drawing::Font^ font, System::Drawing::Rectangle bounds)
	{
		if (m_voxelRes == NULL)
			return;

		for (int j = 0; j < bounds.Height-40; j++)
		{
			int color = m_voxelRes->getColorValue(((float)((bounds.Height-40)-j))/(bounds.Height-40), m_isolines, m_levels);
			if (color >= 0)
			{
				System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(
					GetRValue(color), GetGValue(color), GetBValue(color)));
				graphics->DrawLine(pen, bounds.Left, bounds.Top+j+20, bounds.Right-60, bounds.Top+j+20);
			}
		}

		System::String^ format = "{0:f2}";
		float maxValue = m_voxelRes->getMaxValue()/m_voxelRes->getHist();
		if (maxValue < 0.01f)
			format = "{0:f4}";
		else if (maxValue < 0.1f)
			format = "{0:f3}";

		for (unsigned int j = 0; j <= m_levels; j++)
		{
			float i = (float)j / (float)(m_levels);
			float y = (1.0f-i)*(bounds.Height-40.0f)+20.0f;

			if (m_isolines)
				graphics->DrawLine(System::Drawing::Pens::Black, bounds.Left, bounds.Top+(int)y, bounds.Right-57, bounds.Top+(int)y);
			else
				graphics->DrawLine(System::Drawing::Pens::Black, bounds.Left+bounds.Width-60, bounds.Top+(int)y, bounds.Right-57, bounds.Top+(int)y);

			float value = (float)j/(float)m_levels;

			System::String^ s = (m_percent)
				? System::String::Format("{0}%", (int)(value*100))
				: System::String::Format(format, (value * (m_voxelRes->getMaxValue() - m_voxelRes->getMinValue())) / m_voxelRes->getHist());

			System::Drawing::SizeF strSize = graphics->MeasureString(s, font);
			graphics->DrawString(s, font, System::Drawing::Brushes::Black, bounds.Left+bounds.Width-55.0f, bounds.Top+y-strSize.Height/2.0f);
		}

		graphics->DrawRectangle(System::Drawing::Pens::Black, bounds.Left, bounds.Top+20, bounds.Width-60, bounds.Height-40);
	}

	void DrawCross(System::Drawing::Graphics^ graphics, System::Drawing::Size size)
	{
		UpdateCrossCenter(size);
		System::Drawing::Point crossCenter = AbsToPoint(m_crossCenter, size);
		
		if (crossCenter.Y >= 20 && crossCenter.Y <= size.Height - 20)
		{
			graphics->DrawLine(System::Drawing::Pens::White, 40, crossCenter.Y, size.Width - 20, crossCenter.Y);
			graphics->DrawLine(m_dotPen, 40, crossCenter.Y, size.Width - 20, crossCenter.Y);
		}

		if (crossCenter.X >= 40 && crossCenter.X <= size.Width - 20)
		{
			graphics->DrawLine(System::Drawing::Pens::White, crossCenter.X, 20, crossCenter.X, size.Height - 20);
			graphics->DrawLine(m_dotPen, crossCenter.X, 20, crossCenter.X, size.Height - 20);
		}
	}

	void UpdateCrossCenter(System::Drawing::Size size)
	{
		if (m_crossCenter.IsEmpty)
			m_crossCenter = PointToAbs(System::Drawing::Point((size.Width - 60) / 2 + 40, (size.Height - 40) / 2 + 20), size, true);
	}

	System::Drawing::Point PointToAbs(System::Drawing::Point location, System::Drawing::Size size, bool center)
	{
		if (center)
		{
			// Центрируем на размер voxel
			location.X += ((float)(size.Width - 60) / (float)m_bounds.Width) / 2;
			location.Y += ((float)(size.Height - 40) / (float)m_bounds.Height) / 2;
		}

		int x = m_bounds.X + (int)(((float)(location.X - 40) * (float)m_bounds.Width) / (float)(size.Width - 60));
		int y = m_bounds.Y + (int)(((float)(location.Y - 20) * (float)m_bounds.Height) / (float)(size.Height - 40));
		return System::Drawing::Point(x, y);
	}

	System::Drawing::Point AbsToPoint(System::Drawing::Point point, System::Drawing::Size size)
	{
		int x = (int)(((float)(point.X - m_bounds.X) * (float)(size.Width - 60)) / (float)m_bounds.Width + 40);
		int y = (int)(((float)(point.Y - m_bounds.Y) * (float)(size.Height - 40)) / (float)m_bounds.Height + 20);
		return System::Drawing::Point(x, y);
	}

private:
	void CalcGridParams(int% left, int% right, int% step)
	{
		int e = (int)(log10((float)(right-left)));
		float d = (right - left)/pow(10.0f, e+1);

		if (d < 0.1f)
		{
			step = (int)(0.1f*pow(10.0f, e));
		}
		else if (d < 0.25f)
		{
			step = (int)(0.25f*pow(10.0f, e));
		}
		else if (d < 0.5)
		{
			step = (int)(0.5f*pow(10.0f, e));
		}
		else
		{
			step = (int)(pow(10.0f, e));
		}

		if (step == 0)
			step = 1;

		left = (int)((float)left/(float)step)*step;
		right = (int)((float)right/(float)step)*step;
	}
};

}