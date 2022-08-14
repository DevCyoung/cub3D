using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows;
using System.Drawing;

namespace WinFormsApp5
{
    
    public struct vf2d
    {
        public float x;
        public float y;
        public vf2d(float x, float y)
        {
            this.x = x;
            this.y = y;
        }
    }

    public struct vi2d
    {
        public int x;
        public int y;
        public vi2d(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    public struct rayhit
    {
        public float distH;
        public float distV;
        public float dist;
        public rayhit(float distH, float distV)
        {
            this.distH = distH;
            this.distV = distV;
            this.dist = distH > distV ? distH : distV;
        }
            
    }
    
    public float Dist(float ax, float ay, float bx, float by, float ang)
    {
            return (MathF.Sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
    }

     

    public partial class Form1 : Form
    {

        Rectangle _rect;
        Vector dir = new Vector(0, 0);
        float px = 0f;
        float py = 0f;
        float pdx = 0f;
        float pdy = 0f;
        float pa = 1.24f;

        float PI = 3.14159265359f;
        float P2;
        float P3;
        float DR = 0.0174533f;
        bool debug = false;

        int mapX = 8, mapY = 8, MapS = 64;
        int[] map =
        {
            1,1,1,1,1,1,1,1,
            1,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,1,
            1,0,0,1,1,0,0,1,
            1,0,0,1,1,0,0,1,
            1,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,1,
            1,1,1,1,1,1,1,1,
        };
        public Form1()
        {
            InitializeComponent();

            px = 2.5f;
            py = 2.5f;
            this.Size = new Size(1024, 560);
            panel1.Size = new Size(1024, 560);
            panel1.BackColor = Color.Gray;
            this.DoubleBuffered = true;
            pdx = MathF.Cos(pa);
            pdy = MathF.Sin(pa);
            P2 = PI / 2;
            P3 = 3 * PI / 2;
        }

        public void DrawMap2D(Graphics g)
        {
            SolidBrush b;
            g = panel1.CreateGraphics();
            for (int y = 0; y < mapX; y++)
            {
                for (int x = 0; x < mapY; x++)
                {

                    if (map[mapX * y + x] == 1)
                    {
                        b = new SolidBrush(Color.White);
                    }
                    else
                    {
                        b = new SolidBrush(Color.Black);
                    }
                    Rectangle rect = new Rectangle(x * MapS, y * MapS, MapS, MapS);
                    g.FillRectangle(b, rect);
                }
            }
        }

      
        public rayhit raycast(Graphics g, vf2d start, float radian, float maxdist)
        {
            float deltax = MathF.Cos(radian);
            float deltay = MathF.Sin(radian);

            vf2d vRayStart = start;
            vf2d vRaydir = new vf2d(deltax, deltay);
            vf2d vRayUnitStepSize = new vf2d(MathF.Sqrt(1 + (vRaydir.y / vRaydir.x) * (vRaydir.y / vRaydir.x)),
                                             MathF.Sqrt(1 + (vRaydir.x / vRaydir.y) * (vRaydir.x / vRaydir.y)));
            vi2d vMapCheck = new vi2d(((int)vRayStart.x) , ((int)vRayStart.y));
            vf2d vRayLength1D = new vf2d(0,0);

            vi2d vStep = new vi2d(0,0);


            if (vRaydir.x < 0)
            {
                vStep.x = -1;
                vRayLength1D.x = (vRayStart.x - (float)vMapCheck.x) * vRayUnitStepSize.x;
            }
            else
            {
                vStep.x = 1;
                vRayLength1D.x = (((float)vMapCheck.x + 1) - vRayStart.x) * vRayUnitStepSize.x;
            }

            if (vRaydir.y < 0)
            {
                vStep.y = -1;
                vRayLength1D.y = (vRayStart.y - (float)vMapCheck.y) * vRayUnitStepSize.y;
            }
            else
            {
                vStep.y = 1;
                vRayLength1D.y = (((float)vMapCheck.y + 1) - vRayStart.y) * vRayUnitStepSize.y;
            }

            bool bTileFound = false;
            float fDistance = 0f;
            rayhit hit = new rayhit();
            while (bTileFound == false && fDistance < maxdist)
            {
                if (vRayLength1D.x < vRayLength1D.y)
                {
                    vMapCheck.x += vStep.x;
                    fDistance = vRayLength1D.x;
                    hit.distH = vRayLength1D.x;
                    vRayLength1D.x += vRayUnitStepSize.x;
                }
                else
                {
                    vMapCheck.y += vStep.y;
                    fDistance = vRayLength1D.y;
                    hit.distV = vRayLength1D.y;
                    vRayLength1D.y += vRayUnitStepSize.y;
                }

                if (vMapCheck.x >= 0 && vMapCheck.x < 8 && vMapCheck.y >= 0 && vMapCheck.y < 8)
                {
                    if (map[vMapCheck.y * 8 + vMapCheck.x] == 1)
                    {
                        bTileFound = true;
                    }
                }
            }
            vf2d vIntersecton = new vf2d(vRayStart.x, vRayStart.y);
            if (bTileFound)
            {
                vIntersecton.x = vRayStart.x + vRaydir.x * fDistance;
                vIntersecton.y = vRayStart.y + vRaydir.y * fDistance;
            }
            Pen pen = new Pen(Color.Red, 1);
            g.DrawLine(pen, vRayStart.x * 64, vRayStart.y * 64, vIntersecton.x * 64, vIntersecton.y * 64);
            hit.dist = Dist(vRayStart.x * 64, vRayStart.y * 64, vIntersecton.x * 64, vIntersecton.y * 64, radian);
            

            return hit;
            
        }
    
        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {


            if (e.KeyChar == 'a')
            {
                pa -= 0.1f;
                if (pa < 0)
                    pa += 2 * PI;
                pdx = MathF.Cos(pa);
                pdy = MathF.Sin(pa);

            }
            if (e.KeyChar == 'd')
            {
                pa += 0.1f;
                if (pa > 2 * PI)
                    pa -= 2 * PI;
                pdx = MathF.Cos(pa);
                pdy = MathF.Sin(pa);

            }
            if (e.KeyChar == 'w')
            {
                px += pdx * 0.2f;
                py += pdy * 0.2f;
            }
            if (e.KeyChar == 's')
            {
                px -= pdx * 0.2f;
                py -= pdy * 0.2f;
            }
            if (e.KeyChar == 'b')
            {
                debug = true;
            }
            //Console.Clear();
            //Console.WriteLine($"raydir pdx : {pdx} raydir pdy :{pdy}");
            //Console.WriteLine($"px : {px} py : {py}");
            Refresh();
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g;
            Brush b;
            Pen p;
            //Map
            g = panel1.CreateGraphics();
            DrawMap2D(g);

            //Player
            b = new SolidBrush(Color.Yellow);
            int worldposx = (int)(px * 64);
            int worldposy = (int)(py * 64);
            _rect = new Rectangle((int)(worldposx - 5), (int)(worldposy - 5), 10, 10);
            
            g.FillRectangle(b, _rect);

            //player direction
            p = new Pen(Color.Yellow, 5);
           // g.DrawLine(p, px, py, px + pdx * 10, py + pdy * 10);
           g.DrawLine(p, worldposx, worldposy, worldposx + pdx * 25, worldposy + pdy * 25);
            //raycastin
            //DrawRays3D(g);

            float ra = pa - DR * 30;
            //ra = pa - DR;
            for (int r = 0; r < 60; r++)
            {
                if (ra < 0) { ra += 2 * PI; }
                if (ra > 2 * PI) { ra -= 2 * PI; }
                float ca = pa - ra;
                rayhit hit = raycast(g, new vf2d(px, py), ra, 10);
                float distT = hit.dist * MathF.Cos(ca);
                //Draw -- 3D
                if (ca < 0)
                    ca += 2 * PI;
                if (ca > 2 * PI)
                    ca -= 2 * PI;
                
                float lineH = (MapS * 320) / distT;
                if (lineH > 320)
                {
                    lineH = 320;
                }
                float lineO = 160 - lineH / 2;
                ra += DR;
                Color c;

                //sky
                c = Color.SkyBlue;
                p = new Pen(c, 8);
                g.DrawLine(p, r * 8 + 530, 0, r * 8 + 530, lineO);

                if (hit.distH < hit.distV)
                    c = Color.FromArgb((int)(255 * 0.9f), 0, 0);
                else
                    c = Color.FromArgb((int)(255 * 0.75f), 0, 0);

                p = new Pen(c, 8);
                g.DrawLine(p, r * 8 + 530, lineO, r * 8 + 530, lineH + lineO);
            }
            g.Dispose();
        }
    }
}
