// SPDX-License-Identifier: MIT
pragma solidity 0.8.0;


contract Auction {
   uint private currentBidAmount;
   bytes32 private currentWinner;
   uint256 private finalDate;
   address payable private issuer;


   constructor() {
       finalDate = block.timestamp + 24 hours;
       issuer = payable(msg.sender);
   }


   modifier ifIssuer() {
       require(issuer == msg.sender, "Solo el emisor del contrato puede realizar esta accion.");
       _;
   }


   function bid(bytes32 candidate) public payable {
       require(block.timestamp < finalDate, "La subasta ha finalizado.");
       require(msg.value > currentBidAmount, "La nueva oferta debe ser mayor que la oferta actual.");
       currentBidAmount = msg.value;
       currentWinner = candidate;
   }


   function getCurrentWinner() public view returns(bytes32) {
       return currentWinner;
   }


   function getCurrentWinnerAmount() public view returns(uint) {
       return currentBidAmount;
   }


   function withdrawBid() public ifIssuer {
       issuer.transfer(currentBidAmount);
   }
}
