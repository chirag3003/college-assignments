/**
 * Definition for singly-linked list.
 * public class ListNode {
 * int val;
 * ListNode next;
 * ListNode() {}
 * ListNode(int val) { this.val = val; }
 * ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */

class Solution {

    public ListNode mergeKLists(ListNode[] lists) {
        if (lists.length == 0) {
            return null;
        }
        ListNode result = lists[0];
        for (int i = 1; i < lists.length; i++) {
            if (lists[i] == null) {
                continue;
            }
            result = mergeTwoLists(result, lists[i]);
        }
        return result;
    }

    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null) {
            return l2;
        }
        ListNode result = l1.val < l2.val ? l1 : l2;
        ListNode list = l1.val < l2.val ? l2 : l1;
        ListNode current = result;
        while (current != null && list != null) {
            if (current.val <= list.val) {
                ListNode temp = current.next;
                if (temp == null || temp.val > list.val) {
                    ListNode temp2 = list.next;
                    list.next = temp;
                    current.next = list;
                    list = temp2;
                    current = current.next;
                } else if (temp != null) {
                    current = current.next;
                }
            }
        }
        if (list != null) {
            current.next = list;
        }
        return result;
    }

    // public static void main(String[] args) {
    // Solution s = new Solution();
    // ListNode l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    // ListNode l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    // ListNode l3 = new ListNode(2, new ListNode(6));
    // ListNode[] lists = { l1, l2, l3 };
    // ListNode result = s.mergeKLists(lists);
    // while (result != null) {
    // System.out.println(result.val);
    // result = result.next;
    // }
    // }
}