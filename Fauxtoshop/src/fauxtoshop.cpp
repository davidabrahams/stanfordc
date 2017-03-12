// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: rewrite this comment

#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "gevents.h"
#include "functional"
#include "math.h" //for sqrt and exp in the optional Gaussian kernel
#include "gmath.h" // for sinDegrees(), cosDegrees(), PI
using namespace std;

static const int    WHITE = 0xFFFFFF;
static const int    BLACK = 0x000000;
static const int    GREEN = 0x00FF00;

void     doFauxtoshop(GWindow &gw, GBufferedImage &img);

bool     openImageFromFilename(GBufferedImage& img, string filename);
bool 	 saveImageToFilename(const GBufferedImage &img, string filename);
void     getMouseClickLocation(int &row, int &col);
Vector<double> gaussKernelForRadius(int radius);

/* STARTER CODE FUNCTION - DO NOT EDIT
 *
 * This main simply declares a GWindow and a GBufferedImage for use
 * throughout the program. By asking you not to edit this function,
 * we are enforcing that the GWindow have a lifespan that spans the
 * entire duration of execution (trying to have more than one GWindow,
 * and/or GWindow(s) that go in and out of scope, can cause program
 * crashes).
 */
int main() {
    GWindow gw;
    gw.setTitle("Fauxtoshop");
    gw.setVisible(true);
    GBufferedImage img;
    doFauxtoshop(gw, img);
    return 0;
}

bool loadImageFile(GBufferedImage &img) {
    bool success = false;
    while (!success) {
        string fn = getLine("Which file would you like to open? [Blank to exit]");
        if (fn.empty())
            return false;
        success = openImageFromFilename(img, fn + ".jpg");
        if (!success)
            cout << "Invalid filename entered. Try again." << endl;
    }
    return true;
}

bool inBounds(Grid<int> &img, int &r, int &c) {
    if (r < 0 || c < 0)
        return false;
    if (r >= img.numRows() || c >= img.numCols())
        return false;
    return true;
}

int scatter(Grid<int> &grid, int &r, int &c, int &radius) {
    int y = randomInteger(max(r-radius,0), min(r+radius, grid.numRows()-1));
    int x = randomInteger(max(c-radius,0), min(c+radius, grid.numCols()-1));
    return grid[y][x];
}

void applyFunc(Grid<int> &grid, std::function<int(Grid<int>, int, int)> f) {
    Grid<int> newImage = Grid<int>(grid.numRows(), grid.numCols());
    for (int r = 0; r < grid.numRows(); r++) {
        for (int c = 0; c < grid.numCols(); c++) {
            newImage[r][c] = f(grid, r, c);
        }
    }
    grid = newImage;
}


bool validChoice(int &choice, int& lower, int& upper) {
    if (choice < lower)
        return false;
    if (choice > upper)
        return false;
    return true;
}

int filterChoice(int lower, int upper) {
    int choice = -1;
    while (!validChoice(choice, lower, upper)) {
        choice = getInteger();
        if (!validChoice(choice, lower, upper))
            cout << "Please enter a valid option" << endl;
    }
    return choice;
}

/* This is yours to edit. Depending on how you approach your problem
 * decomposition, you will want to rewrite some of these lines, move
 * them inside loops, or move them inside helper functions, etc.
 *
 * TODO: rewrite this comment.
 */
void doFauxtoshop(GWindow &gw, GBufferedImage &img) {

    cout << "Welcome to Fauxtoshop!" << endl;
    gw.add(&img,0,0);
    bool loop = true;
    while (loop) {
        if (!loadImageFile(img)) {
            loop = false;
            continue;
        }
        gw.setCanvasSize(img.getWidth(), img.getHeight());
        cout << "Which image filter would you like to apply?"<< endl;
        cout << "\t1: Scatter" << endl;
        cout << "\t1: Edge Detection" << endl;
        int choice = filterChoice(1, 2);
        Grid<int> grid = img.toGrid();
        if (choice == 1) {
            int radius = -1;
            while (radius < 1 || radius > 100)
                radius = getInteger("What is your scatter radius? [1-100]");
            auto lambda =[&radius] (Grid<int> g, int r, int c) { return scatter(g, r, c, radius); };
            cout << "Applying scatter..." << endl;
            applyFunc(grid, lambda);
            img.fromGrid(grid);
        }
        cout << "Operation complete." << endl << endl;
    }
        //    GBufferedImage img2;
//    openImageFromFilename(img2, "beyonce.jpg");
//    img.countDiffPixels(img2);

//    int row, col;
//    getMouseClickLocation(row, col);
//    gw.clear();
    cout << "Exiting" << endl;
    gw.close();
}


/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to open the image file 'filename'.
 *
 * This function returns true when the image file was successfully
 * opened and the 'img' object now contains that image, otherwise it
 * returns false.
 */
bool openImageFromFilename(GBufferedImage& img, string filename) {
    try { img.load(filename); }
    catch (...) { return false; }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to save the image file to 'filename'.
 *
 * This function returns true when the image was successfully saved
 * to the file specified, otherwise it returns false.
 */
bool saveImageToFilename(const GBufferedImage &img, string filename) {
    try { img.save(filename); }
    catch (...) { return false; }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Waits for a mouse click in the GWindow and reports click location.
 *
 * When this function returns, row and col are set to the row and
 * column where a mouse click was detected.
 */
void getMouseClickLocation(int &row, int &col) {
    GMouseEvent me;
    do {
        me = getNextEvent(MOUSE_EVENT);
    } while (me.getEventType() != MOUSE_CLICKED);
    row = me.getY();
    col = me.getX();
}

/* HELPER FUNCTION
 *
 * This is a helper function for the Gaussian blur option.
 *
 * The function takes a radius and computes a 1-dimensional Gaussian blur kernel
 * with that radius. The 1-dimensional kernel can be applied to a
 * 2-dimensional image in two separate passes: first pass goes over
 * each row and does the horizontal convolutions, second pass goes
 * over each column and does the vertical convolutions. This is more
 * efficient than creating a 2-dimensional kernel and applying it in
 * one convolution pass.
 *
 * This code is based on the C# code posted by Stack Overflow user
 * "Cecil has a name" at this link:
 * http://stackoverflow.com/questions/1696113/how-do-i-gaussian-blur-an-image-without-using-any-in-built-gaussian-functions
 *
 */
Vector<double> gaussKernelForRadius(int radius) {
    if (radius < 1) {
        Vector<double> empty;
        return empty;
    }
    Vector<double> kernel(radius * 2 + 1);
    double magic1 = 1.0 / (2.0 * radius * radius);
    double magic2 = 1.0 / (sqrt(2.0 * PI) * radius);
    int r = -radius;
    double div = 0.0;
    for (int i = 0; i < kernel.size(); i++) {
        double x = r * r;
        kernel[i] = magic2 * exp(-x * magic1);
        r++;
        div += kernel[i];
    }
    for (int i = 0; i < kernel.size(); i++) {
        kernel[i] /= div;
    }
    return kernel;
}
