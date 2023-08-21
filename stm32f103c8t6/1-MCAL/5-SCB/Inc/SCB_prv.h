#ifndef SCB_RRV_H_
#define SCB_RRV_H_

#define PRIORITY_GROUPING_MIN           (0U)
#define PRIORITY_GROUPING_MAX           (7U)

#define VECTKEY_POS                     (16U)
#define VECTKEY_MASK                    (0xFFFFU)
#define VECTKEY                         (VECTKEY_MASK << VECTKEY_POS)
#define VECTKEY_VALUE                   (0x05FAU)
#define VECTKEYSTAT_POS                 (16U)
#define VECTKEYSTAT_VALUE               (0xFA05U)

#define PRIGROUP_POS                    (8U)
#define PRIGROUP_MASK                   (0x07U)
#define PRIGROUP                        (PRIGROUP_MASK << PRIGROUP_POS)

#endif /* SCB_PRV_H_ */