public class recursion {
    public static int factorial(int n){
        int aux=0;
        if(n==0 || n==1){
            return 1;
        }else{
            aux=n*factorial(n-1);
            return aux;
        }
    }
    
    public static void main(String[] args) {
        System.out.println("hola");
        int x=3;
        int result= factorial(x);
        System.out.println(result);
    }
    
}
