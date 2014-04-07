#include "Polygon2d.h"

#include <stdio.h>

Polygon2D::Polygon2D(void)
{
	length = 0;
}

Polygon2D::Polygon2D(int length, Edge2d* edges)
{
	this->length = length;

	this->edges = new Edge2d[length];
	this->points = new Vector3[length];
	this->normals = new Vector3[length];

	for (int i = 0; i < length; i++)
	{
		this->edges[i] = edges[i];
		this->points[i] = edges[i].o;
	}
}

Polygon2D Polygon2D::getBoundBox(void)
{
	float minX, maxX, minY, maxY;
	minX = minY =  99999999;
	maxX = maxY = -99999999;

	Edge2d edge;
	float x, y;
	for (int i = 0; i < length; i++)
	{
		edge = edges[i];
		x = edge.o.x;
		y = edge.o.y;

		if(x > maxX)
		{
			maxX = x;
		}
		if(y > maxY)
		{
			maxY = y;
		}
		if(x < minX)
		{
			minX = x;
		}
		if(y < minY)
		{
			minY = y;
		}

		x = edge.p.x;
		y = edge.p.y;

		if(x > maxX)
		{
			maxX = x;
		}
		if(y > maxY)
		{
			maxY = y;
		}
		if(x < minX)
		{
			minX = x;
		}
		if(y < minY)
		{
			minY = y;
		}
	}
	
	Edge2d* bounding = new Edge2d[4];
	bounding[0] = Edge2d(new Vector3(minX, maxY), new Vector3(maxX, maxY));
	bounding[1] = Edge2d(new Vector3(minX, minY), new Vector3(maxX, minY));
	bounding[2] = Edge2d(new Vector3(minX, minY), new Vector3(minX, maxY));
	bounding[3] = Edge2d(new Vector3(maxX, minY), new Vector3(maxX, maxY));

	return Polygon2D(4, bounding);
}

void Polygon2D::printConsole(void)
{
	printf("Polygon:\nEdges:\n");

	for (int i = 0; i < length; i++)
	{
		this->edges[i].printConsole();
	}

	printf("Normals:\n");

	for(int i = 0; i < length; i++)
	{
		this->normals[i].printConsole();
	}
}

void Polygon2D::calculateOuter(void)
{
	int j = 0;
	int k = 0;
	Vector3 compare;
	for(int i = 0; i < length; i++)
	{
		j = (i+1)%length;
		k = (i+2)%length;

		if(points[j].x == points[i].x)
		{
			j = (i+2)%length;
			k = (i+3)%length;
		}

		float x = -(points[j].y - points[i].y)/(points[j].x - points[i].x);
		float y = 1.f;
		normals[i] = Vector3(x,y);
		
		x = points[k].x - points[i].x;
		y = points[k].y - points[i].y;
		compare = Vector3(x,y);

		float dot = normals[i].dotProduct(compare);
		if(dot > 0)
		{
			normals[i].x *= -1;
			normals[i].y *= -1;
		}
	}
}

/*
float t1,t2,t,num,den;
  Point2D dirV,F;          // vectors
  int I;
  
    // start largest at smallest legal value and smallest 
    // at largest legal value
  t1 = 0.0;
  t2 = 1.0;
   // compute the direction vector
  dirV.x = p2.x - p1.x;
  dirV.y = p2.y - p1.y;

  visible = TRUE;
  i = 0;
  while ( (i < p.nPoints) && visible)
  { F.x = p1.x - p.v[i].x;
    F.y = p1.y - p.v[i].y;
    
    num  = DotProduct (n[i],F);
    den   =  DotProduct (n[i],dirV);

    if (den == 0.0)          // Parallel or Point
    { // parallel - if outside then forget the line; if inside then there are no 
      // intersections with this side 
      // but there may be with other edges, so in this case just keep going
       if (num > 0.0)
        visible = FALSE;   //   Parallel and outside or point (p1 == p2) and outside
    }
    else 
    { t = -(num/den);
      if (den < 0.0)        // entering
      { if (t <= 1.0)
          if (t > t1)
            t1 = t;
      }
      else if ( t >= 0.0)    //exiting
        if (t < t2)
          t2 = t;
    }
    i++;
  }
  if ( t1 <= t2)
  { rp.x = p1.x + t1*dirV.x;
    rp.y = p1.y + t1*dirV.y;
    q.x = p1.x + t2.dirV.x
    q.y = p1.y + t2*dirV.y
  }
  else
    visible = FALSE;
*/