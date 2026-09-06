---
config:
  layout: fixed
---
flowchart LR
 subgraph MCU["Microcontroller (e.g., Arduino Uno)"]
    direction TB
        GND_MCU["&nbsp;GND<br>(Negative)&nbsp;"]
        5V_MCU["5V / 3.3V<br>(Positive)"]
        SDA_MCU["SDA<br>"]
        SCL_MCU["SCL<br>"]
  end
 subgraph I2C_PORT["I2C Port"]
    direction TB
        GND_I2C["GND"]
        5V_I2C["&nbsp;5V&nbsp;"]
        SDA_I2C["SDA"]
        SCL_I2C["SCL"]
  end
 subgraph DOMINO_PORT["Domino Port"]
    direction TB
        E_PLUS["E+"]
        E_MINUS["E-"]
        S_PLUS["S+"]
        S_MINUS["&nbsp;S-&nbsp;"]
  end
 subgraph I2C_BOARD["MKE-S18 I2C HX710 Loadcell Board"]
    direction TB
        I2C_PORT
        DOMINO_PORT
  end
 subgraph LOADCELL["Loadcell Sensor 1Kg"]
    direction TB
        BLACK_WIRE["Black Wire<br>(Power -)"]
        RED_WIRE["Red Wire<br>(Power +)"]
        GREEN_WIRE["Green Wire<br>(Signal +)"]
        WHITE_WIRE["White Wire<br>(Signal -)"]
  end
    GND_MCU == Black Wire ==> GND_I2C
    5V_MCU == Red Wire ==> 5V_I2C
    SDA_MCU == Yellow Wire ==> SDA_I2C
    SCL_MCU == Green Wire ==> SCL_I2C
    E_PLUS ----- RED_WIRE
    E_MINUS ----- BLACK_WIRE
    S_PLUS ----- GREEN_WIRE
    S_MINUS ----- WHITE_WIRE

     BLACK_WIRE:::black
     RED_WIRE:::red
     GREEN_WIRE:::green
     WHITE_WIRE:::white
    classDef mcu fill:#f2f9f9,stroke:#0f9d58,stroke-width:2px
    classDef board fill:#fdf5e6,stroke:#fbbc05,stroke-width:2px
    classDef loadcell fill:#fce8e6,stroke:#ea4335,stroke-width:2px
    classDef black fill:#333,color:#fff
    classDef red fill:#ea4335,color:#fff
    classDef green fill:#34a853,color:#fff
    classDef white fill:#fbfbfb,stroke:#ccc
    style DOMINO_PORT fill:#34a853
    style LOADCELL fill:#BBDEFB
    style I2C_BOARD fill:#C8E6C9
    style MCU fill:#FFF9C4
    linkStyle 0 stroke:#333,stroke-width:3px,fill:none
    linkStyle 1 stroke:#D50000,stroke-width:3px,fill:none
    linkStyle 2 stroke:#fbbc05,stroke-width:3px,fill:none
    linkStyle 3 stroke:#0f9d58,stroke-width:3px,fill:none