typedef unsigned int u32 ;

typedef struct{



 void *GPIO_PORT ;

 u32 GPIO_PIN ;

 u32 GPIO_MODE ;

 u32 GPIO_SPEED ;

}GPIO_t;





typedef enum

{

 GPIO_enuOK ,

 GPIO_enuNullpointer,

 GPIO_enuunvalidpin,

 GPIO_enuunvalidParameter ,

 GPIO_enuunvalidstate ,

 GPIO_enuunvalidport ,

 GPIO_enuunvalidmode,

 GPIO_enuNOK



} GPIO_enuErrorStatus_t ;



GPIO_enuErrorStatus_t GPIO_INITPIN (GPIO_t * GPIO_CFG);

GPIO_enuErrorStatus_t GPIO_SET_PINVALUE (void * GPIO_PORT ,u32 GPIO_PIN , u32 GPIO_STATE );

GPIO_enuErrorStatus_t GPIO_GET_PINVALUE (void * GPIO_PORT ,u32 GPIO_PIN , u32 * GPIO_STATE);

GPIO_enuErrorStatus_t GPIO_AF_CFG (void * GPIO_PORT ,u32 GPIO_PIN , u32 GPIO_Func);
