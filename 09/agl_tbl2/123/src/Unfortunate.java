import java.util.concurrent.locks.ReentrantLock;

public class Unfortunate extends Thread {
	private Unfortunate[] mUnfortunates;
	private int mIndex;
	private int mFeedIndex;
	private volatile boolean mEating;
	public volatile boolean mFeeding;

	public Unfortunate(int index, Unfortunate[] unfortunates) {
		mUnfortunates = unfortunates;
		mIndex = index;
		mFeedIndex = (index + 1) % unfortunates.length;
	}

	public void run() {
		while (true) {
			try {
				feedOther();
				Thread.sleep(600);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public void feedOther() throws InterruptedException {
		while (mEating);

		mFeeding = true;
		while (mUnfortunates[mFeedIndex].mFeeding);

		mUnfortunates[mFeedIndex].eat();
		mFeeding = false;
	}

	public void eat() throws InterruptedException {
		mEating = true;
		System.out.println("Thread " + mIndex + " eating....");
		Thread.sleep(500);
		mEating = false;
	}
}
