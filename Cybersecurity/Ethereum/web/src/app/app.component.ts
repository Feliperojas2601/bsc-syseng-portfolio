import { CommonModule } from '@angular/common';
import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { RouterOutlet } from '@angular/router';
import Web3 from 'web3';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, RouterOutlet, FormsModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  web3: any;
  auctionContract: any;
  amount!: number;
  candidate!: string;
  result!: string;

  constructor() {
    this.web3 = new Web3('http://localhost:8552'); 
    const contractABI = [
      {
        "inputs": [
          {
            "internalType": "bytes32",
            "name": "candidate",
            "type": "bytes32"
          }
        ],
        "name": "bid",
        "outputs": [],
        "stateMutability": "payable",
        "type": "function"
      },
      {
        "inputs": [],
        "stateMutability": "nonpayable",
        "type": "constructor"
      },
      {
        "inputs": [],
        "name": "withdrawBid",
        "outputs": [],
        "stateMutability": "nonpayable",
        "type": "function"
      },
      {
        "inputs": [],
        "name": "getCurrentWinner",
        "outputs": [
          {
            "internalType": "bytes32",
            "name": "",
            "type": "bytes32"
          }
        ],
        "stateMutability": "view",
        "type": "function"
      },
      {
        "inputs": [],
        "name": "getCurrentWinnerAmount",
        "outputs": [
          {
            "internalType": "uint256",
            "name": "",
            "type": "uint256"
          }
        ],
        "stateMutability": "view",
        "type": "function"
      }
    ];
    const contractAddress = '0xc8e605241Cf5af2f4F36153A9a157bD21b4F2DB7'; 
    this.auctionContract = new this.web3.eth.Contract(contractABI, contractAddress);
  }

  async placeBid() {
    try {
      const accounts = await this.web3.eth.getAccounts(); // Obtener cuentas del usuario
      await this.auctionContract.methods.bid(this.stringToBytes32(this.candidate)).send({
        from: accounts[0], // Utiliza la primera cuenta del usuario
        value: this.web3.utils.toWei(this.amount.toString(), 'ether'), // Convierte la cantidad a wei
      });
      this.result = 'Oferta realizada correctamente.';
    } catch (error: any) {
      console.error('Error al realizar la oferta:', error);
      this.result = 'Error al realizar la oferta: ' + error.message;
    }
  }

  public stringToBytes32(text: string): string {
    let result = this.web3.utils.utf8ToHex(text);
    return result;
  }

  public bytes32ToString(text: string): string {
    let result = this.web3.utils.hexToUtf8(text);
    return result;
  }

  async getCurrentWinner() {
    try {
      const winner = await this.auctionContract.methods.getCurrentWinner().call();
      this.result = 'El ganador actual es: ' + this.bytes32ToString(winner);
    } catch (error: any) {
      console.error('Error al obtener el ganador actual:', error);
      this.result = 'Error al obtener el ganador actual: ' + error.message;
    }
  }

  async getCurrentWinnerAmount() {
    try {
      const amount = await this.auctionContract.methods.getCurrentWinnerAmount().call();
      this.result = 'La cantidad del ganador actual es: ' + this.web3.utils.fromWei(amount, 'ether') + ' Ether';
    } catch (error: any) {
      console.error('Error al obtener la cantidad del ganador actual:', error);
      this.result = 'Error al obtener la cantidad del ganador actual: ' + error.message;
    }
  }

  async withdrawBid() {
    try {
      const accounts = await this.web3.eth.getAccounts(); // Obtener cuentas del usuario
      await this.auctionContract.methods.withdrawBid().send({
        from: accounts[0], // Utiliza la primera cuenta del usuario
      });
      this.result = 'Oferta retirada correctamente.';
    } catch (error: any) {
      console.error('Error al retirar la oferta:', error);
      this.result = 'Error al retirar la oferta: ' + error.message;
    }
  }
}

