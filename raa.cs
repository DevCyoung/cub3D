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

    public struct box
    {
        public Bitmap bitmap;
    }



    public enum wall_dir
    { 
        NONE = 0,
        EAST,
        WESET,
        NORTH,
        SOUTH
    }

    public struct rayhit
    {
        public float distH;
        public float distV;
        public float dist;
        public bool hit;
        public int type;
        public wall_dir wall;
        public Color color;
        public vf2d hitpoint;
        public vi2d mapPoint;
        public rayhit(float distH, float distV)
        {
            this.distH = distH;
            this.distV = distV;
            this.dist = distH > distV ? distH : distV;
            this.hit = false;
            this.type = 1;
            this.wall = wall_dir.NONE;
            this.color = Color.White;
            hitpoint = new vf2d(0, 0);
            mapPoint = new vi2d(0, 0);
        }
            
    }

    public partial class Form1 : Form
    {

        Rectangle _rect;
        float px = 0f;
        float py = 0f;
        float pdx = 0f;
        float pdy = 0f;
        float pa = 1.74f;

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

        const int windowSizeX = 1024;
        const int windowSizeY = 560;

        int mapX = 32, mapY = 32, MapS = 32 * 32;

        float st = 330f;

        int mapCameraSizeX = 5;
        int mapCameraSizeY = 5;

        Bitmap bitmap1;
        Bitmap bitmap2;
        Bitmap bitmap3;
        Bitmap bitmap4;
        Bitmap bitmap5;

        int[] map =
        {
            2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            3,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            3,3,0,0,4,2,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            3,0,0,0,4,2,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            3,0,4,0,0,4,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            3,0,0,1,0,0,0,0,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,3,3,3,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
            1,1,0,0,3,3,0,0,2,2,1,1,1,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,3,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
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

        int texture_x;
        int texture_y;
        int texture_size;
        int[] texture =
        {
            2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
            2,3,3,3,3,0,0,0,0,0,3,3,3,3,3,2,
            2,3,1,1,1,0,4,4,4,0,1,1,1,1,3,2,
            2,3,1,1,1,0,4,4,4,0,1,1,1,1,3,2,
            2,3,1,1,1,0,4,4,4,0,1,1,1,1,3,2,
            2,3,1,1,1,1,1,1,1,1,1,1,1,1,3,2,
            2,3,1,1,1,1,1,1,1,1,1,1,1,1,3,2,
            2,3,1,1,1,1,1,1,1,1,1,1,1,1,3,2,            
            2,3,1,1,1,1,1,1,1,1,1,1,1,1,3,2,
            2,3,1,1,1,1,1,1,1,1,1,1,1,1,3,2,
            2,3,1,1,1,1,1,1,1,1,1,1,1,1,3,2,
            2,3,1,1,1,0,4,4,4,0,1,1,1,1,3,2,
            2,3,1,1,1,0,4,4,4,0,1,1,1,1,3,2,
            2,3,1,1,1,0,4,4,4,0,1,1,1,1,3,2,
            2,3,3,3,3,0,0,0,0,0,3,3,3,3,3,2,
            2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        };
        

        public Form1()
        {
            InitializeComponent();

            px = 5.5f;
            py = 6.5f;
            this.Size = new Size(windowSizeX, windowSizeY);
            panel1.Size = new Size(windowSizeX, windowSizeY);
            panel1.BackColor = Color.Gray;

            this.DoubleBuffered = true;
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.BackColor = Color.Gray;
            panel1.Invalidate();
            pdx = MathF.Cos(pa);
            pdy = MathF.Sin(pa);
            P2 = PI / 2;
            P3 = 3 * PI / 2;

            DR = 0.0174533f / (float)my_size;
            startra = DR * 30 * my_size;
            raysize = (int)(60 * my_size);
            len = 8 / my_size;
            isray = false;

            bitmap1 = new Bitmap(@"C:\Users\tkdlq\source\repos\WinFormsApp5\WinFormsApp5\Resources\Brick_wall.bmp");
            bitmap2 = new Bitmap(@"C:\Users\tkdlq\source\repos\WinFormsApp5\WinFormsApp5\Resources\Water.bmp");
            bitmap3 = new Bitmap(@"C:\Users\tkdlq\source\repos\WinFormsApp5\WinFormsApp5\Resources\Dehydrated_Earth.bmp");
            bitmap4 = new Bitmap(@"C:\Users\tkdlq\source\repos\WinFormsApp5\WinFormsApp5\Resources\eagle.bmp");
            bitmap5 = new Bitmap(@"C:\Users\tkdlq\source\repos\WinFormsApp5\WinFormsApp5\Resources\redbrick.bmp");

            texture_x = bitmap1.Width;
            texture_y = bitmap1.Height;
            texture_size = texture_x * texture_y;

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

        public int diff(int a, int b)
        {
            return a > b ? a - b : b - a;
        }

        public void drawLine(Graphics g, vi2d start, vi2d end, Color color)
        {
            //if (start.x >= end.x)
            //{
            //    vi2d temp = start;
            //    start = end;
            //    end = temp;
            //}

            //if (start.y >= end.y)
            //{
            //    vi2d temp = start;
            //    start = end;
            //    end = temp;
            //}

            vi2d delta = new vi2d(end.x - start.x, end.y - start.y);
            int step = Math.Abs(delta.x) > Math.Abs(delta.y) ? Math.Abs(delta.x) : Math.Abs(delta.y);
            //int step = (delta.x) >(delta.y) ? (delta.x) : (delta.y);

            float xinc = delta.x / (float)(step);
            float yinc = delta.y / (float)(step);

            vf2d cur_pos = new vf2d((float)start.x, (float)start.y);

            for (int i = 0; i < step; i++)
            {
                g.FillRectangle(new SolidBrush(color), (int)cur_pos.x, (int)cur_pos.y, 1, 1);
                cur_pos.x += xinc;
                cur_pos.y += yinc;
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
                if (vMapCheck.x >= 0 && vMapCheck.x < mapX && vMapCheck.y >= 0 && vMapCheck.y < mapY)
                {
                    if (map[vMapCheck.y * mapX + vMapCheck.x] != 0)
                    {
                        bTileFound = true;
                        hit.type = map[vMapCheck.y * mapX + vMapCheck.x];
                    }
                }
                hit.type = 1;
            }
            vf2d vIntersecton = new vf2d(vRayStart.x, vRayStart.y);

            if (bTileFound && fDistance < maxdist)
            {
                vIntersecton.x = vRayStart.x + vRaydir.x * fDistance;
                vIntersecton.y = vRayStart.y + vRaydir.y * fDistance;
                hit.hit = true;
                //hit.wall = wall_dir.EAST;
                if (hit.distH < hit.distV)
                {
                    if (vRaydir.y > 0.000f)
                    {
                        hit.wall = wall_dir.WESET;
                        hit.color = Color.Blue;
                    }
                    else
                    {
                        hit.wall = wall_dir.EAST;
                        hit.color = Color.Yellow;
                    }
                }
                else
                {
                    if (vRaydir.x > 0.000f)
                    {
                        hit.wall = wall_dir.SOUTH;
                        hit.color = Color.Red;
                    }
                    else
                    {
                        hit.wall = wall_dir.NORTH;
                        hit.color = Color.Green;
                    }
                }

            }
            else
            {
                vIntersecton.x = vRayStart.x + vRaydir.x * maxdist;
                vIntersecton.y = vRayStart.y + vRaydir.y * maxdist;
                hit.hit = false;
            }
            hit.hitpoint = vIntersecton;
            hit.mapPoint = vMapCheck;
            if (isray)
            {
                Pen pen = new Pen(color, 1);
                g.DrawLine(pen, vRayStart.x * mapPxel, vRayStart.y * mapPxel, vIntersecton.x * mapPxel, vIntersecton.y * mapPxel);
            }
            else
            {
                Pen p;
                //if (map[vMapCheck.y * mapX + vMapCheck.x] == 1)
                //{
                //    p = new Pen(Color.Red, 1);
                //}
                //else if (map[vMapCheck.y * mapX + vMapCheck.x] == 2)
                //{
                //    p = new Pen(Color.Green, 1);
                //}
                //else if (map[vMapCheck.y * mapX + vMapCheck.x] == 3)
                //{
                //    p = new Pen(Color.Blue, 1);
                //}
                //else
                //{
                //    p = new Pen(Color.Yellow, 1);
                //}
                if (map[vMapCheck.y * mapX + vMapCheck.x] == 1)
                {
                    //switch (hit.wall)
                    //{
                    //    case wall_dir.NONE:
                    //        hit.color = Color.White;
                    //        break;
                    //    case wall_dir.EAST:
                    //        hit.color = Color.Red;
                    //        break;
                    //    case wall_dir.WESET:
                    //        hit.color = Color.Green;
                    //        break;
                    //    case wall_dir.NORTH:
                    //        hit.color = Color.Blue;
                    //        break;
                    //    case wall_dir.SOUTH:
                    //        hit.color = Color.Yellow;
                    //        break;
                    //    default:
                    //        break;
                    //}
                }
                p = new Pen(hit.color, 1);
                //g.DrawLine(p, vRayStart.x * mapPxel, vRayStart.y * mapPxel, vIntersecton.x * mapPxel, vIntersecton.y * mapPxel);
                vi2d s = new vi2d((int)(vRayStart.x * mapPxel), (int)(vRayStart.y * mapPxel));
                vi2d e = new vi2d((int)(vIntersecton.x * mapPxel), (int)(vIntersecton.y * mapPxel));
                drawLine(g, s, e, hit.color);
            }
            
            hit.dist = Dist(vRayStart.x * mapPxel, vRayStart.y * mapPxel, vIntersecton.x * mapPxel, vIntersecton.y * mapPxel, radian);
            return hit;
            
        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
          
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
                    px -= pdx * 0.1f;
                    py -= pdy * 0.1f;
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
            if (e.KeyChar == 'q')
            {
                st--;
                Console.WriteLine($"st : {st}");
            }
            if (e.KeyChar == 'e')
            {
                st++;
                Console.WriteLine($"st : {st}");
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
            bff.Graphics.FillRectangle(new SolidBrush(Color.Gray), 0, 0, windowSizeX, windowSizeY);
            
            SolidBrush b;

            //for (int y = 0; y < mapY; y++)
            //{
            //    for (int x = 0; x < mapX; x++)
            //    {
            //        if (map[mapX * y + x] == 1)
            //        {
            //            b = new SolidBrush(Color.White);
            //        }
            //        else if (map[mapX * y + x] == 2)
            //        {
            //            b = new SolidBrush(Color.White);
            //        }
            //        else if (map[mapX * y + x] == 3)
            //        {
            //            b = new SolidBrush(Color.White);
            //        }
            //        else if (map[mapX * y + x] == 4)
            //        {
            //            b = new SolidBrush(Color.White);
            //        }
            //        else
            //        {
            //            b = new SolidBrush(Color.Black);
            //        }
            //        Rectangle rect = new Rectangle(x * mapPxel, y * mapPxel, mapPxel, mapPxel);
            //        bff.Graphics.FillRectangle(b, rect);
            //    }
            //}
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
                    else if (map[mapX * y + x] == 4)
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
                //if (ca < 0)
                //    ca += 2 * PI;
                //if (ca > 2 * PI)
                //    ca -= 2 * PI;
                rayhit hit = raycast(bff.Graphics, new vf2d(px, py), ra, 40, Color.Green);
                float distT = (hit.dist / mapPxel) * MathF.Cos(ca);
                //Draw -- 3D
                if (ca < 0)
                    ca += 2 * PI;
                if (ca > 2 * PI)
                    ca -= 2 * PI;

                if (hit.hit == true)
                {

                    float lineH = (windowSizeY / 1.5f) / distT;
                    float lineO = ((windowSizeY - 100) / 2) - lineH / 2;
                    Color c;

                    //sky
                    int lineoff = (int)(lineO + lineH);
                    c = Color.SkyBlue;
                    p = new Pen(c, len);
                    bff.Graphics.DrawLine(p   , r * len + windowSizeX / 2 + 5,       0, r * len + windowSizeX / 2 + 5, lineO);
                    //bff.Graphics.DrawLine(p, r * len + windowSizeX / 2 + 5, lineO, r * len + windowSizeX / 2 + 5, lineH + lineO);
                    Bitmap bmp = bitmap1;
                   

                    //box
                    c = hit.color;
                    int tm = 0;
                   

                    p = new Pen(c, len);
                    int pivot = (int)lineO;
                    bmp = bitmap1;
                    if (hit.wall == wall_dir.EAST)
                    {
                        bmp = bitmap1;
                    }
                    else if (hit.wall == wall_dir.WESET)
                    {
                        bmp = bitmap2;
                    }
                    else if (hit.wall == wall_dir.SOUTH)
                    {
                        bmp = bitmap3;
                    }
                    else
                        bmp = bitmap4;

                    float gd = 1f;
                    if (hit.distH < hit.distV)
                    {
                        c = Color.FromArgb(c.R, c.G, c.B);
                        gd = 1f;
                        tm = (int)(((hit.hitpoint.x) - (int)(hit.hitpoint.x)) * bmp.Width);
                    }
                    else
                    {
                        c = Color.FromArgb((int)(c.R * 0.75f),
                                           (int)(c.G * 0.75f),
                                           (int)(c.B * 0.75f));
                        gd = 0.75f;
                        tm = (int)(((hit.hitpoint.y) - (int)(hit.hitpoint.y)) * bmp.Width);
                    }



                    float step = bmp.Height / lineH;
                    //texture_size = 1024;
                    float ty = 0;
                    for (int i = 0; i < lineH; i++)
                    {
                        Color tc = bmp.GetPixel(tm % bmp.Width, (int)ty % bmp.Height);
                        tc = Color.FromArgb((int)(tc.R * gd), (int)(tc.G * gd), (int)(tc.B * gd));
                        bff.Graphics.FillRectangle(new SolidBrush(tc), r * len + windowSizeX / 2 + 2, pivot + i, len, 1);
                        ty += step;
                    }                   
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
