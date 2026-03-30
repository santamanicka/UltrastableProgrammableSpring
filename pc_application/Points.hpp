using namespace std;

class Point
{
public:
    Point();
    ~Point();
    void SetPoint(double X, double Y) { XPos = X; YPos = Y; }

    double XPos;
    double YPos;
private:

    static int NumberOfPoints;
};

int Point::NumberOfPoints = 0;

Point::Point()
{
	NumberOfPoints++;
    XPos = 0.0;
    YPos = 0.0;
}

Point::~Point()
{
	NumberOfPoints--;
}
 