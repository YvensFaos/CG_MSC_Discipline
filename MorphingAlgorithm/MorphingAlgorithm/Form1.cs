using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MorphingAlgorithm
{
    public partial class Form1 : Form
    {
        bool line1;
        bool line2;

        Point p1;
        Point p2;

        List<Line> lines1 = new List<Line>();
        List<Line> lines2 = new List<Line>();

        Graphics gStart;
        Graphics gFinish;
        Graphics gStep;

        Image startImg;
        Image finishImg;

        Bitmap startBmp;
        Bitmap finishBmp;
        
        public Form1()
        {
            InitializeComponent();

            line1 = false;
            line2 = false;

            this.panelStart.Paint += PanelStart_Paint;
            this.panelFinish.Paint += PanelFinish_Paint;
            this.panelStep.Paint += PanelStep_Paint;
        }

        private void PanelStart_Paint(object sender, PaintEventArgs e)
        {
            startImg = Image.FromFile("C:\\Users\\Yvens\\Documents\\GitHub\\DisciplinaCG\\MorphingAlgorithm\\MorphingAlgorithm\\imgs\\start.jpeg");
            startBmp = (Bitmap)startImg;
            startBmp = new Bitmap(startBmp, 374, 388);
            if (gStart == null)
            {
                gStart = e.Graphics;
            }

            e.Graphics.DrawImage(startImg, 0, 0, 374, 388);

            foreach (Line l in lines1)
            {
                e.Graphics.DrawLine(Pens.Red, l.p1, l.p2);
            }
        }

        private void PanelFinish_Paint(object sender, PaintEventArgs e)
        {
            finishImg = Image.FromFile("C:\\Users\\Yvens\\Documents\\GitHub\\DisciplinaCG\\MorphingAlgorithm\\MorphingAlgorithm\\imgs\\finish.jpeg");
            finishBmp = (Bitmap)finishImg;
            finishBmp = new Bitmap(finishBmp, 374, 388);
            if (gFinish == null)
            {
                gFinish = e.Graphics;
            }

            e.Graphics.DrawImage(finishImg, 0, 0, 374, 388);

            foreach (Line l in lines2)
            {
                e.Graphics.DrawLine(Pens.Blue, l.p1, l.p2);
            }
        }

        private void PanelStep_Paint(object sender, PaintEventArgs e)
        {
            if (gStep == null)
            {
                gStep = e.Graphics;
            }

            Bitmap bmp = new Bitmap(panelStep.Width, panelStep.Height);
            Rectangle rec = new Rectangle(0, 0, 374, 388);
            if (startBmp != null)
            {
                for (int i = 0; i < panelStep.Width; i++)
                {
                    for (int j = 0; j < panelStep.Height; j++)
                    {
                        Color p1 = startBmp.GetPixel(i, j);
                        Color p2 = finishBmp.GetPixel(i, j);

                        int r = Math.Abs(p1.R - p2.R);
                        int b = Math.Abs(p1.B - p2.B);
                        int g = Math.Abs(p1.G - p2.G);

                        bmp.SetPixel(i, j, Color.FromArgb(r, g, b));
                    }
                }
            }
            
            e.Graphics.DrawImage(bmp, rec);
        }

        private void PanelStart_Click(object sender, EventArgs e)
        {
            Panel panel = (Panel)sender;
            Point point = panel.PointToClient(Cursor.Position);

            if (!line1)
            {
                p1 = point;
                line1 = true;
            }
            else
            {
                lines1.Add(new Line(point, p1));
                line1 = false;

                labelStart.Text = "Qtde: " + lines1.Count + " Adicionado: " + point + " e " + p1;

                panel.Invalidate();
            }
        }

        private void PanelFinish_Click(object sender, EventArgs e)
        {
            Panel panel = (Panel)sender;
            Point point = panel.PointToClient(Cursor.Position);

            if (!line2)
            {
                p2 = point;
                line2 = true;
            }
            else
            {
                lines2.Add(new Line(point, p2));
                line2 = false;

                labelFinish.Text = "Qtde: " + lines2.Count + " Adicionado: " + point + " e " + p2;

                panel.Invalidate();
            }
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (lines1.Count > 0)
            {
                lines1.RemoveAt(lines1.Count - 1);
            }

            panelStart.Invalidate();
        }

        private void buttonFinish_Click(object sender, EventArgs e)
        {
            if (lines2.Count > 0)
            {
                lines2.RemoveAt(lines2.Count - 1);
            }

            panelFinish.Invalidate();
        }

        private void buttonStep_Click(object sender, EventArgs e)
        {
            panelStep.Invalidate();
            //paintStep();
        }

        private void paintStep()
        {
            Graphics gr = panelStep.CreateGraphics();

            Bitmap bmp = new Bitmap(374, 388);
            if (startBmp != null)
            {
                for (int i = 0; i < panelStep.Width; i++)
                {
                    for (int j = 0; j < panelStep.Height; j++)
                    {
                        Color p1 = startBmp.GetPixel(i, j);
                        Color p2 = finishBmp.GetPixel(i, j);

                        int r = (p1.R + p2.R) / 2;
                        int b = (p1.B + p2.B) / 2;
                        int g = (p1.G + p2.G) / 2;

                        bmp.SetPixel(i, j, Color.FromArgb(r, g, b));
                    }
                }
            }

            gr.DrawImage(bmp, 0, 0, 374, 388);

            panelStep.Invalidate();
        }
    }

    class Line
    {
        public Point p1;
        public Point p2;

        public Line(Point p1, Point p2)
        {
            this.p1 = p1;
            this.p2 = p2;
        }
    }
}
