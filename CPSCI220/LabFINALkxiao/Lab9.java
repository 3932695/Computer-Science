// CPSCI 220 - Lab 9 - Kevin Xiao - Due April 22nd 2014
// No other students were consulted for this lab.

import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.util.*;

// Adjust size of window here. Ball maximum size will vary with window size.
class Global{
    public static int width = 800;
    public static int height = 640;
    public static int minimum = Math.min(width, height);
}


// Initializes attributes of a standard 'SimpleBall' object.
class SimpleBall extends JPanel {
    public int delay = 10;
    public int x; public int y; // Current ball position.
    public int radius; // Ball size/radius.
    public int dx = 2; // 'x velocity'.
    public int dy = 2; // 'y velocity'. 
    private Random rn = new Random();
    public Color randomColor;
    
    // Color, radius, and x-axis starting location are randomized. 
    public SimpleBall(){
	x = rn.nextInt(Global.minimum);
	y = 0;
	radius = rn.nextInt(Global.minimum/10) + 5;
	float r = rn.nextFloat();
	float g = rn.nextFloat();
	float b = rn.nextFloat();
	randomColor = new Color(r, g, b);
    }
}

// Balls inherits many features of BallLab9.
class Balls extends BallLab9 {

    // Addition: an ArrayList of SimpleBalls.
    private ArrayList<SimpleBall> array = new ArrayList<SimpleBall>();
    public Balls(){
	super();
    }

    // Addition: a method to add SimpleBalls to the ArrayList.
    public void addBall(){
	array.add(new SimpleBall());
    }

    // Addition: a method to remove SimpleBalls from the ArrayList.
    public void removeBall(){
	if(array.size() > 0){
	    array.remove(array.size() - 1);
	}
    }
    
    // AWKWARD DESIGN NOTE:
    // Ideally I'd inherit some of this method via super.paintComponent(g).
    // However doing so would introduce a 'ball' with private fields.
    // This 'private ball' is very undesirable due to the collision feature.
    // Thus instead of using super.paintComponent(g)...
    // ...I have chosen to wipe the canvas with every update instead.
    @Override
    protected void paintComponent(Graphics g){
	g.setColor(new Color(238, 238, 238));
	g.fillRect(0, 0, getWidth(), getHeight());
	for (int i = 0; i < array.size(); i++){

	    // Collision algorithms for border.
	    if (array.get(i).x < 0)
		array.get(i).dx = 1;
	    if (array.get(i).x > getWidth())
		array.get(i).dx = -1;
	    if (array.get(i).y < 0)
		array.get(i).dy = 1;
	    if (array.get(i).y > getHeight())
		array.get(i).dy = -1;

	    // Collision function for balls.
	    collision(array.get(i), array);
	    
	    // Update ball position.
	    array.get(i).x += array.get(i).dx;
	    array.get(i).y += array.get(i).dy;

	    int x = array.get(i).x;
	    int y = array.get(i).y;
	    int radius = array.get(i).radius;
	
	    // Draw the ball(s) with available information.
	    g.setColor(array.get(i).randomColor);
	    g.fillOval(x - radius, y - radius, radius * 2, radius * 2);
	}
    }

    // Collision function contains collision algorithms for balls. 
    private void collision(SimpleBall ball, ArrayList<SimpleBall> array){
	// Compares current ball with every other ball in the array.
	for (int i = 0; i < array.size(); i++){
	    if (ball != array.get(i)){
		double xDif = ball.x - array.get(i).x;
		double yDif = ball.y - array.get(i).y;
		double hypSquared = xDif * xDif + yDif * yDif;
		double radSum = ball.radius + array.get(i).radius;
		boolean collision = hypSquared <= (radSum * radSum);
		if(collision){
		    if(xDif >= yDif){
			if(xDif < 0){
			    ball.dx = -1;
			    array.get(i).dx = 1;
			}else{
			    ball.dx = 1;
			    array.get(i).dx = -1;
			}
		    }
		    if(xDif <= yDif){
			if(yDif < 0){
			    ball.dy = -1;
			    array.get(i).dy = 1;
			}else{
			    ball.dy = 1;
			    array.get(i).dy = -1;
			}
		    }

		}
			
	    }
	}

    }
    
       
    
}

// User interface objects handled here.
// BallControlLab9 fields are private and lack public methods for access.
// Recreating with modifications is preferable to extending.
class ExtendedControlLab9 extends JPanel {
    private Balls ball = new Balls();
    private JButton jbtStop = new JButton("Stop");
    private JButton jbtStart = new JButton("Start");
    private JScrollBar jsbDelay = new JScrollBar();
    private JButton jbtadd1 = new JButton("+1");
    private JButton jbtsub1 = new JButton("-1");

    public ExtendedControlLab9() {

	// Group buttons in a panel.
	final JPanel panel = new JPanel();
	panel.add(jbtStop);
	panel.add(jbtadd1);
	panel.add(jbtsub1);

	// Add ball and buttons to the panel.
	ball.setBorder(new javax.swing.border.LineBorder(Color.red));
	jsbDelay.setOrientation(JScrollBar.HORIZONTAL);
	ball.setDelay(jsbDelay.getMaximum());
	setLayout(new BorderLayout());
	add(jsbDelay, BorderLayout.NORTH);
	add(ball, BorderLayout.CENTER);
	add(panel, BorderLayout.SOUTH);

	// Register 'listeners' for the buttons (capture input).
	jbtadd1.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    ball.addBall();
		}
	    });
	jbtsub1.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    ball.removeBall();
		}
	    });
	jbtStop.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    ball.suspend();
		    panel.remove(jbtStop);
		    panel.add(jbtStart, 0);
		    panel.revalidate();
		    panel.repaint();
		}
	    });
	jbtStart.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    ball.resume();
		    panel.remove(jbtStart);
		    panel.add(jbtStop, 0);
		    panel.revalidate();
		    panel.repaint();
		}
	    });
	jsbDelay.addAdjustmentListener(new AdjustmentListener() {
		public void adjustmentValueChanged(AdjustmentEvent e) {
		    ball.setDelay(jsbDelay.getMaximum() - e.getValue());
		}
	    });

    }

}

public class Lab9 extends JApplet {
    public Lab9() {
	add(new ExtendedControlLab9());
    
    }

    public static void main(String[] args) {
	Lab9 applet = new Lab9();
	JFrame frame = new JFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setTitle("Bouncing Balls Extended");
	frame.add(applet, BorderLayout.CENTER);
	frame.setSize(Global.width, Global.height);
	frame.setVisible(true);

    }
}

