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
    public struct Vector
    {
        public float _x;
        public float _y;
        public Vector(float x, float y)
        {
            _x = x;
            _y = y;
        }
    }

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
        public bool hit;
        public int type;
        public rayhit(float distH, float distV)
        {
            this.distH = distH;
            this.distV = distV;
            this.dist = distH > distV ? distH : distV;
            this.hit = false;
            this.type = 1;
        }
            
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
        bool debug = false;
        bool ismove = true;
        bool[] move_dir = new bool[2] { true, true };


        int mapPxel = 16;


        int my_size = 1;
        float DR;
        float startra;
        int raysize;
        float len;
        bool isray;

        int mapX = 32, mapY = 32, MapS = 32 * 32;
        int[] map =
        {
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,1,0,0,2,2,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,2,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,3,3,3,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
            1,1,0,0,2,2,0,0,2,2,1,1,1,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,2,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,1,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
            1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
            1,0,1,0,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
            1,1,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
            1,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

        };


        int deltaX = 0;
        void mouse_realtime_location(object sender, MouseEventArgs e)
        {
            //deltaX = e.Location.X - deltaX;
            //if (deltaX > 1)
            //{
            //    pa -= 0.1f;
            //    if (pa < 0)
            //        pa += 2 * PI;
            //    pdx = MathF.Cos(pa);
            //    pdy = MathF.Sin(pa);

            //}
            //else
            //{
            //    pa += 0.1f;
            //    if (pa > 2 * PI)
            //        pa -= 2 * PI;
            //    pdx = MathF.Cos(pa);
            //    pdy = MathF.Sin(pa);
            //}
            //panel1.Invalidate();
        }

        public Form1()
        {
            InitializeComponent();

            px = 3.5f;
            py = 4.5f;
            this.Size = new Size(1024, 560);
            panel1.Size = new Size(1024, 560);
            panel1.BackColor = Color.Gray;

            this.DoubleBuffered = true;
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.BackColor = Color.Gray;
            panel1.Invalidate();
            pdx = MathF.Cos(pa);
            pdy = MathF.Sin(pa);
            P2 = PI / 2;
            P3 = 3 * PI / 2;
            panel1.MouseMove += new MouseEventHandler(mouse_realtime_location);

            DR = 0.0174533f / (float)my_size;
            startra = DR * 30 * my_size;
            raysize = (int)(60 * my_size);
            len = 8 / my_size;
            isray = false;

        }

        public void DrawMap2D(Graphics g)
        {
            SolidBrush b;
            for (int y = 0; y < mapX; y++)
            {
                for (int x = 0; x < mapY; x++)
                {

                    if (map[mapX * y + x] == 1)
                    {
                        b = new SolidBrush(Color.White);
                    }
                    else if (map[mapX * y + x] == 2)
                    {
                        b = new SolidBrush(Color.White);
                    }
                    else if (map[mapX * y + x] == 3)
                    {
                        b = new SolidBrush(Color.White);
                    }
                    else
                    {
                        b = new SolidBrush(Color.Black);
                    }
                    Rectangle rect = new Rectangle(x * mapPxel, y * mapPxel, mapPxel, mapPxel);
                    g.FillRectangle(b, rect);
                }
            }
        }

        public float Dist(float ax, float ay, float bx, float by, float ang)
        {
            return (MathF.Sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
        }

        public void DDAShot(Graphics g)
        {
            Vector rayUnitStepSize = new Vector(MathF.Sqrt(1 + (pdy / pdx) * (pdy / pdx)), MathF.Sqrt(1 + (pdx / pdy) * (pdx / pdy)));
            Vector mapCheck = new Vector(px, py);
            Vector raydir = new Vector(pdx, pdy);
            Vector step;
            Vector raylength1D;




            if (raydir._x < 0)
            {
                step._x = -1;
                //raylength1D._x = (px)
            }
            else
            {
                step._x = 1;
            }

            if (raydir._y < 0)
            {
                step._y = -1;
            }
            else
            {
                step._y = 1;
            }

        }

        public void DrawRays3D(Graphics g)
        {
            int mx, my, mp, dof;
            float rx, ry, ra, xo, yo, disT;

            ra = pa-DR*30;
            //ra = pa - DR;
            if (ra < 0) { ra += 2 * PI; }
            if (ra > 2 * PI) { ra -= 2 * PI; }

            for (int r = 0; r < 1; r++)
            {
                //Horizontal Lines
                dof = 0;
                float disH = 1000000, hx = px, hy = py;
                float aTan = -(1 / MathF.Tan(ra));
                rx = pdx;
                ry = pdy;
                xo = 0;
                yo = 0;


                if (ra > PI) 
                { 
                    ry = (((int)py >> 6) << 6) - 0.001f; 
                    rx = (py - ry) * aTan + px; 
                    yo = -64; 
                    xo = -yo * aTan; 
                }
                if (ra < PI)
                { 
                    ry = (((int)py >> 6) << 6) + 64f;    
                    rx = (py - ry) * aTan + px; 
                    yo =  64; 
                    xo = -yo * aTan; }
                if (ra == 0 || ra == PI) 
                { 
                    rx = px; 
                    ry = py;
                    dof = 8; 
                }


                while (dof < 8)
                {
                    mx = (int)(rx) >> 6; 
                    my = (int)(ry) >> 6; 
                    mp = my * mapX + mx;
                    g.FillEllipse(new SolidBrush(Color.Aqua), new Rectangle((int)rx - 5, (int)ry - 5, 10, 10));
                    if (debug == true)
                    {

                    }
                    if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
                    {
                        hx = rx;
                        hy = ry;
                        disH = Dist(px, py, hx, hy, ra);
                        dof = 10;
                    }
                    else 
                    {
                        rx += xo; 
                        ry += yo; 
                        dof += 1;
                    }
                }

                //g.DrawLine(new Pen(Color.Green, 3), px, py, rx, ry);

                dof = 0;
                float disV = 1000000, vx = px, vy = py;
                float nTan = -MathF.Tan(ra);
                rx = pdx;
                ry = pdy;
                xo = 0;
                yo = 0;
                //Look down
                if (ra > P2 && ra < P3) { rx = ((((int)px) >> 6) << 6) - 0.00001f; ry = (px - rx) * nTan + py; xo = -64; yo = -xo * nTan; }
                if (ra < P2 || ra > P3) { rx = ((((int)px) >> 6) << 6) + 64f; ry = (px - rx) * nTan + py; xo = 64; yo = -xo * nTan; }
                if (ra == 0 || ra == PI) { rx = px; ry = py; dof = 8; }

                while (dof < 8)
                {
                    
                    
                    mx = (int)(rx) >> 6; 
                    my = (int)(ry) >> 6; 
                    mp = my * mapX + mx;
                    //g.FillEllipse(new SolidBrush(Color.Gold), new Rectangle((int)rx - 5, (int)ry - 5, 10, 10));
                    if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
                    {
                        vx = rx;
                        vy = ry;
                        disV = Dist(px, py, vx, vy, ra);
                        dof = 8;
                    }
                    else
                    {
                        rx += xo;
                        ry += yo;
                        dof += 1;
                    }
                }
                Color color;
                if (disV < disH) 
                {                  
                    rx = vx; 
                    ry = vy; 
                    disT = disV;
                    color = Color.FromArgb((int)(0.9 * 255), 0, 0);
                }
                else
                { 
                    rx = hx; 
                    ry = hy; 
                    disT = disH;
                    color = Color.FromArgb((int)(0.7 * 255), 0, 0);
                }
                g.DrawLine(new Pen(Color.Green, 1), px, py, rx, ry);

                //Draw -- 3D
                float ca = pa - ra; 
                if (ca < 0) { ca += 2 * PI; } 
                if (ca > 2 * PI) { ca -= 2 * PI; } 
                disT = disT * MathF.Cos(ca);
                float lineH = (MapS * 320) / disT; 
                if (lineH>320) { lineH = 320; }
                float lineO = 160 - lineH / 2;
                if (isray)
                {
                    Pen p = new Pen(color, 8);
                    g.DrawLine(p, r * 8 + 530, lineO, r * 8 + 530, lineH + lineO);

                }
                ra += DR;
                if (ra < 0) { ra += 2 * PI; } if (ra > 2 * PI) { ra -= 2 * PI; }
            }
        }


        public rayhit raycast(Graphics g, vf2d start, float radian, float maxdist, Color color)
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
                hit.type = 1;
                if (vMapCheck.x >= 0 && vMapCheck.x < mapX && vMapCheck.y >= 0 && vMapCheck.y < mapY)
                {
                    if (map[vMapCheck.y * mapX + vMapCheck.x] != 0)
                    {
                        bTileFound = true;
                        hit.type = map[vMapCheck.y * mapX + vMapCheck.x];
                    }
                }
            }
            vf2d vIntersecton = new vf2d(vRayStart.x, vRayStart.y);

            if (bTileFound && fDistance < maxdist)
            {
                vIntersecton.x = vRayStart.x + vRaydir.x * fDistance;
                vIntersecton.y = vRayStart.y + vRaydir.y * fDistance;
                hit.hit = true;
            }
            else
            {
                vIntersecton.x = vRayStart.x + vRaydir.x * maxdist;
                vIntersecton.y = vRayStart.y + vRaydir.y * maxdist;
                hit.hit = false;
            }
            
            if (isray)
            {
                Pen pen = new Pen(color, 1);
                g.DrawLine(pen, vRayStart.x * mapPxel, vRayStart.y * mapPxel, vIntersecton.x * mapPxel, vIntersecton.y * mapPxel);
            }
            else
            {
                Pen p;
                if (map[vMapCheck.y * mapX + vMapCheck.x] == 1)
                {
                    p = new Pen(Color.Red, 1);
                }
                else if (map[vMapCheck.y * mapX + vMapCheck.x] == 2)
                {
                    p = new Pen(Color.Green, 1);
                }
                else if (map[vMapCheck.y * mapX + vMapCheck.x] == 3)
                {
                    p = new Pen(Color.Blue, 1);
                }
                else
                {
                    p = new Pen(Color.Yellow, 1);
                }
                
                g.DrawLine(p, vRayStart.x * mapPxel, vRayStart.y * mapPxel, vIntersecton.x * mapPxel, vIntersecton.y * mapPxel);
            }
            
            hit.dist = Dist(vRayStart.x * mapPxel, vRayStart.y * mapPxel, vIntersecton.x * mapPxel, vIntersecton.y * mapPxel, radian);
            

            return hit;
            
        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
          
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            pa -= 0.1f;
            pdx = MathF.Cos(pa);
            pdy = MathF.Sin(pa);
            
            if (e.Delta > 0)
            {
                pa -= 0.1f;
                if (pa < 0)
                    pa += 2 * PI;
                pdx = MathF.Cos(pa);
                pdy = MathF.Sin(pa);

            }
            else if (e.X < 0)
            {
                pa += 0.1f;
                if (pa > 2 * PI)
                    pa -= 2 * PI;
                pdx = MathF.Cos(pa);
                pdy = MathF.Sin(pa);

            }
            panel1.Invalidate();
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
                if (move_dir[0] == true)
                {
                    px += pdx * 0.2f;
                    py += pdy * 0.2f;
                }
            }
            if (e.KeyChar == 's')
            {
                if (move_dir[1] == true)
                {
                    px -= pdx * 0.2f;
                    py -= pdy * 0.2f;
                }
            }
            if (e.KeyChar == 'r')
            {
                my_size *= 2;
                if (my_size > 8)
                    my_size = 1;
                DR = 0.0174533f / (float)my_size;
                startra = DR * 30 * my_size;
                raysize = (int)(60 * my_size);
                len = 8 / my_size;
                isray = false;
            }
            if (e.KeyChar == 'p')
            {
                if (mapPxel == 4)
                    mapPxel = 16;
                else
                    mapPxel = 4;
            }
            if (e.KeyChar == 'b')
            {
                debug = true;
            }
            //Console.Clear();
            //Console.WriteLine($"raydir pdx : {pdx} raydir pdy :{pdy}");
            //Console.WriteLine($"px : {px} py : {py}");
            //panel1.Refresh();
            panel1.Invalidate();
            //panel1.Refresh();
            //panel1.Update();
        }
     
        
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            //panel1.Invalidate();
            BufferedGraphicsContext cc;
            BufferedGraphics bff;

            cc = BufferedGraphicsManager.Current;
            bff = cc.Allocate(panel1.CreateGraphics(), panel1.ClientRectangle);            
            bff.Graphics.FillRectangle(new SolidBrush(Color.Gray), 0, 0, 1024, 560);
            
            SolidBrush b;
            for (int y = 0; y < mapY; y++)
            {
                for (int x = 0; x < mapX; x++)
                {
                    if (map[mapX * y + x] == 1)
                    {
                        b = new SolidBrush(Color.White);
                    }
                    else if (map[mapX * y + x] == 2)
                    {
                        b = new SolidBrush(Color.White);
                    }
                    else if (map[mapX * y + x] == 3)
                    {
                        b = new SolidBrush(Color.White);
                    }
                    else
                    {
                        b = new SolidBrush(Color.Black);
                    }
                    Rectangle rect = new Rectangle(x * mapPxel, y * mapPxel, mapPxel, mapPxel);
                    bff.Graphics.FillRectangle(b, rect);
                }
            }
            Graphics g;
            Pen p;
            //Map
            g = panel1.CreateGraphics();

            //Player
            b = new SolidBrush(Color.Yellow);
            int worldposx = (int)(px * mapPxel);
            int worldposy = (int)(py * mapPxel);
            _rect = new Rectangle((int)(worldposx - 3), (int)(worldposy - 3), 6, 6);

            bff.Graphics.FillRectangle(b, _rect);

            //player direction
            p = new Pen(Color.Yellow, 5);
            bff.Graphics.DrawLine(p, worldposx, worldposy, worldposx + pdx * 25, worldposy + pdy * 25);

            //raycastin
            //DrawRays3D(g);

            float ra = pa - startra;
            //ra = pa - DR;
            PointF[] pf = new PointF[raysize];
            for (int r = 0; r < raysize; r++)
            {
                if (ra < 0) { ra += 2 * PI; }
                if (ra > 2 * PI) { ra -= 2 * PI; }
                float ca = pa - ra;
                rayhit hit = raycast(bff.Graphics, new vf2d(px, py), ra, 40, Color.Green);
                float distT = hit.dist * MathF.Cos(ca);
                //Draw -- 3D
                if (ca < 0)
                    ca += 2 * PI;
                if (ca > 2 * PI)
                    ca -= 2 * PI;

                if (hit.hit == true)
                {

                    float lineH = (mapPxel * 320) / distT;

                    //if (lineH > 320)
                    //{
                    //    lineH = 320;
                    //}

                    float lineO = 160 - lineH / 2;
                    Color c;

                    //sky
                    c = Color.SkyBlue;
                    p = new Pen(c, len);
                    bff.Graphics.DrawLine(p, r * len + 530, 0, r * len + 530, lineO);



                    

                    //box
                    if (hit.type == 1)
                    {
                        c = Color.Red;
                    }
                    else if (hit.type == 2)
                    {
                        c = Color.Green;
                    }
                    else if (hit.type == 3)
                    {
                        c = Color.Blue;
                    }
                    else
                    {
                        c = Color.Black;
                    }

                    if (hit.distH < hit.distV)
                        c = Color.FromArgb(c.R, c.G, c.B);
                    else
                        c = Color.FromArgb((int)(c.R * 0.65f), 
                                           (int)(c.G * 0.65f), 
                                           (int)(c.B * 0.65f));

                    p = new Pen(c, len);
                    bff.Graphics.DrawLine(p, r * len + 530, lineO, r * len + 530, lineH + lineO);

                }
                ra += DR;
            }

            rayhit w = raycast(bff.Graphics, new vf2d(px, py), pa, 0.65f, Color.Red);
            rayhit s = raycast(bff.Graphics, new vf2d(px, py), pa + PI, 0.65f, Color.Aqua);

            move_dir[0] = !w.hit;
            move_dir[1] = !s.hit;

            bff.Render();
            bff.Dispose();
            g.Dispose();
        }
    }
}
