package Test;

public class TestTwo {
    public static void main(String[] args) {
        String str = "abc,,de,g,,f,,,";
        BinTree binTree = BinTree.initBinTree(str);

        binTree.midOrder();
        System.out.println();

        binTree.postOrder();
        System.out.println();

        System.out.println(binTree.getLeafCount());
        System.out.println(binTree.getDepth());

    }


    static class BinTree {
        private static int count;
        private static char[] chars;
        private BinTree leftChild;
        private BinTree rightChild;
        private char data;

        private BinTree() {
        }

        public static BinTree initBinTree(String str) {
            char[] chs = str.toCharArray();
            return initBinTree(chs);
        }

        public static BinTree initBinTree(char[] chs) {
            count = 0;
            chars = chs;
            BinTree root = new BinTree();
            root.data = chars[count++];
            root.leftChild = createBinTree();
            root.rightChild = createBinTree();
            return root;
        }

        private static BinTree createBinTree() {
            if (chars[count] == ',') {
                count++;
                return null;
            }

            BinTree bt = new BinTree();
            bt.data = chars[count++];

            bt.leftChild = createBinTree();
            bt.rightChild = createBinTree();
            return bt;
        }

        private void preOrder() {
            System.out.print(this.data);
            if (leftChild != null) {
                leftChild.preOrder();
            }
            if (rightChild != null) {
                rightChild.preOrder();
            }
        }

        private void midOrder() {
            if (leftChild != null) {
                leftChild.midOrder();
            }
            System.out.print(this.data);

            if (rightChild != null) {
                rightChild.midOrder();
            }
        }

        private void postOrder() {
            if (leftChild != null) {
                leftChild.postOrder();
            }
            if (rightChild != null) {
                rightChild.postOrder();
            }
            System.out.print(this.data);
        }


        private int getLeafCount() {
            int count = 0;
            if (leftChild == null && rightChild == null) {
                return 1;
            }
            if (leftChild != null) {
                count += leftChild.getLeafCount();
            }
            if (rightChild != null) {
                count += rightChild.getLeafCount();
            }
            return count;
        }

        private int getDepth() {
            int depth = 1;
            int leftChildDepth = 0;
            int rightChildDepth = 0;
            if (leftChild != null) {
                leftChildDepth = leftChild.getDepth();
            }
            if (rightChild != null) {
                rightChildDepth = rightChild.getDepth();
            }
            return leftChildDepth > rightChildDepth ? leftChildDepth + depth : rightChildDepth + depth;
        }
    }
}
